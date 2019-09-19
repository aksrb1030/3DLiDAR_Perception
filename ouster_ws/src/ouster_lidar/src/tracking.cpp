#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/video/tracking.hpp"
#include <cv_bridge/cv_bridge.h>
#include "HungarianAlg.h"

#include <ros/ros.h>
#include <time.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <typeinfo>

#include "std_msgs/String.h"
#include <std_msgs/Float64MultiArray.h>
#include "std_msgs/MultiArrayLayout.h"
#include "std_msgs/MultiArrayDimension.h"
#include "std_msgs/Float32.h"
#include "geometry_msgs/Point32.h"
#include "std_msgs/Header.h"

#include <image_transport/image_transport.h>
#include <sensor_msgs/image_encodings.h>
#include <sensor_msgs/Image.h>
#include <visualization_msgs/Marker.h>
#include <visualization_msgs/MarkerArray.h>
#include <sensor_msgs/PointField.h>
#include <sensor_msgs/PointCloud2.h>
#include <ouster_lidar/MarkerWithCloud.h>
#include <ouster_lidar/MarkerWithCloudArray.h>

#include <pcl/ModelCoefficients.h>
#include <pcl_ros/point_cloud.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/console/time.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/filters/extract_indices.h>
#include <pcl/sample_consensus/method_types.h>
#include <pcl/sample_consensus/model_types.h>
#include <pcl/features/normal_3d.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/segmentation/extract_clusters.h>
#include <pcl/kdtree/kdtree.h>
#include <pcl/filters/passthrough.h>
#include <pcl/common/transforms.h>
#include <pcl/common/common.h>

using namespace std;
using namespace cv;

ros::Subscriber sub_classification_result;
ros::Publisher pub_tracking_box;
ros::Publisher pub_tracking_txt;


vector<geometry_msgs::Point> markerCenter;

vector<Rect2d> markerDetectBB;


int stateVariableDim = 4; //  cx ,cy, dx, dy
int stateMeasureDim = 2;  //  cx, cy
unsigned int nextID = 0;
unsigned int m_thres_invisibleCnt = 4;

//A & Q = Predict process
// A
float dt = 0.1; // assume 20 fps
Mat m_matTransition = (Mat_<float>(stateVariableDim, stateVariableDim) << 1, 0, dt, 0,
                       0, 1, 0, dt,
                       0, 0, 0, 0,
                       0, 0, 0, 0);

//H & R Estimation process
// H
Mat m_matMeasurement = (Mat_<float>(stateMeasureDim, stateVariableDim) << 1, 0, 0, 0,
                        0, 1, 0, 0);

// Q size small -> smooth
float Q[] = {1, 1, 1, 1};
Mat tempQ(stateVariableDim, 1, CV_32FC1, Q);
Mat m_matProcessNoiseCov = Mat::diag(tempQ);

// R
float R[] = {1e-3f, 1e-3f};
Mat tempR(stateMeasureDim, 1, CV_32FC1, R);
Mat m_matMeasureNoiseCov = Mat::diag(tempR);

Mat imgTest;

struct trackingStruct
{
    unsigned int id;
    unsigned int age;
    unsigned int classification;

    float dx;
    float dy;
    float dz;

    KalmanFilter kf;
    unsigned cntTotalVisible;
    unsigned cntConsecutiveInvisible;
    Rect_<float> markerBB;
    // vector<Point2f> clusCen;
    geometry_msgs::Point clusCen;
    geometry_msgs::Point preCen;
    geometry_msgs::Point maxP;
    geometry_msgs::Point minP;
    float ax;
    float ay;
    float az;
    float speed;
    double sec;
};
vector<trackingStruct> vecTracks;
vector<pair<int, int>> vecAssignments;
vector<int> vecUnssignedTracks;
vector<int> vecUnssignedDetections;
float m_thres_associationCost = 5.0f;
visualization_msgs::MarkerArray tracking_marker_array;
visualization_msgs::MarkerArray tracking_text_array;

float returnDis(float x1, float x2, float y1, float y2)
{
    float dis;
    dis = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
    return dis;
}

double distanceCompare(geometry_msgs::Point a, geometry_msgs::Point b)
{
    float distance = (float)sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2) + pow(b.z - a.z, 2));

    // cout<<"Distance : "<< distance <<endl;
    return distance;
}

//  칼만 필터를 사용하여 현재 프레임에서 각 트랙의 중심을 예측하고 이에 따라 경계 상자를 업데이트합니다.
void predictNewLocationOfTracks()
{

    for (int i = 0; i < vecTracks.size(); i++)
    {
        //트랙의 현재 위치를 예측
        vecTracks[i].kf.predict();

        //상자를 중앙에 오도록 이동
        //예측 위치
        vecTracks[i].clusCen.x = vecTracks[i].kf.statePre.at<float>(0);
        vecTracks[i].clusCen.y = vecTracks[i].kf.statePre.at<float>(1);

        vecTracks[i].dx = vecTracks[i].kf.statePre.at<float>(2);
        vecTracks[i].dy = vecTracks[i].kf.statePre.at<float>(3);
    }
}
/*
현재 프레임의 객체 탐지를 기존 트랙에 할당하는 것은 비용을 최소화함으로써 수행됩니다. 비용은 트랙에 대응하는 검출의 음의 로그 가능도 (log-likelihood)로서 정의된다.

이 알고리즘은 두 단계로 구성됩니다.

1 단계 : System object ™ 의 distance방법을 사용하여 모든 탐지를 각 트랙에 할당하는 비용을 계산합니다 vision.KalmanFilter. 비용은 트랙의 예상 중심과 검출 중심 간의 유클리드 거리를 고려합니다. 그것은 또한 칼만 필터에 의해 유지되는 예측의 신뢰도를 포함합니다. 결과는 M × N 매트릭스에 저장되며, 여기서 M은 트랙의 수이고, N은 검출 수이다.

2 단계 : assignDetectionsToTracks함수를 사용하여 비용 행렬로 표시된 할당 문제를 푸십시오 . 이 함수는 비용 매트릭스와 트랙에 탐지를 지정하지 않은 비용을 사용합니다.

트랙에 탐지를 할당하지 않은 비용의 값은의 distance메소드에 의해 반환 된 값의 범위에 따라 달라집니다 vision.KalmanFilter. 이 값은 실험적으로 조정해야합니다. 너무 낮게 설정하면 새 트랙을 만들 가능성이 높아지며 트랙 조각화가 발생할 수 있습니다. 너무 높게 설정하면 일련의 분리 된 움직이는 물체에 해당하는 단일 트랙이 생길 수 있습니다.

이 assignDetectionsToTracks함수는 Munkres의 헝가리 알고리즘 버전을 사용하여 총 비용을 최소화하는 할당을 계산합니다. 두 개의 열에 할당 된 트랙과 탐지의 해당 색인을 포함하는 M x 2 행렬을 반환합니다. 또한 할당되지 않은 채로 남아있는 트랙 및 탐지 항목의 색인을 반환합니다.
*/
void assignDetectionsTracks(const vector<geometry_msgs::Point> &markerCenter)
{
    int N = (int)vecTracks.size();    //  N은 트랙의 수
    int M = (int)markerCenter.size(); //  M은 detection의 수

    vector<vector<double>> Cost(N, vector<double>(M)); //2 array

    // printf("T %d, D %d ",N,M);

    for (int i = 0; i < N; i++)
    {
        // printf(" %d",vecTracks[i].id);
        for (int j = 0; j < M; j++)
        {
            //Box Over Lap
            // Cost[i][j] = 1 - bboxOverlapRatio(vecTracks[i].markerBB, markerDetectBB[j]);
            // Cost[i][j] = 1 - big_bboxOverlapRatio(vecTracks[i].markerBB, markerDetectBB[j]);
            Cost[i][j] = distanceCompare(vecTracks[i].clusCen, markerCenter[j]);

            //High width Box Over Lap
        }
    }
    // printf("\n");

    vector<int> assignment;

    if (N != 0)
    {
        AssignmentProblemSolver APS;
        APS.Solve(Cost, assignment, AssignmentProblemSolver::optimal);
    }

    vecAssignments.clear();
    vecUnssignedTracks.clear();
    vecUnssignedDetections.clear();

    for (int i = 0; i < N; i++)
    {
        if (assignment[i] == -1)
        {
            vecUnssignedTracks.push_back(i);
        }
        else
        {
            if (Cost[i][assignment[i]] < m_thres_associationCost)
            {
                vecAssignments.push_back(pair<int, int>(i, assignment[i]));
                // cout << "fisrt i : " << i << " secnod i : " << assignment[i] << endl;
            }
            else
            {
                vecUnssignedTracks.push_back(i);
                assignment[i] = -1;
            }
        }
    }

    for (int j = 0; j < M; j++)
    {
        auto it = find(assignment.begin(), assignment.end(), j);
        if (it == assignment.end())
            vecUnssignedDetections.push_back(j);
    }
}
/*
이 updateAssignedTracks기능은 할당 된 각 트랙을 해당 검색으로 업데이트합니다. 
위치 추정을 수정 하는 correct방법을 호출합니다 vision.KalmanFilter. 
다음으로, 새로운 바운딩 박스를 저장하고 트랙의 에이지와 총 가시적 인 수를 1 씩 증가시킵니다.
마지막으로이 함수는 보이지 않는 카운트를 0으로 설정합니다.
*/
void assignedTracksUpdate(const vector<geometry_msgs::Point> &markerCenter)
{
    for (int i = 0; i < (int)vecAssignments.size(); i++)
    {
        int idT = vecAssignments[i].first;
        int idD = vecAssignments[i].second;

        Mat meas = Mat::zeros(stateMeasureDim, 1, CV_32FC1);
        meas.at<float>(0) = (float)(markerCenter[idD].x); // cx
        meas.at<float>(1) = (float)(markerCenter[idD].y); // cy
        // meas.at<float>(2) = (float)(markerCenter[idD].z); // cz

        vecTracks[idT].kf.correct(meas);

        double secsCur = ros::Time::now().toSec();
        // cout << "secsCur : " << ros::Time::now().toSec() << endl;
        double diffDt = secsCur - vecTracks[idT].sec;
        float v = 0.0;

        float preDx = vecTracks[idT].dx;
        float preDy = vecTracks[idT].dy;
        float preDz = vecTracks[idT].dz;

        vecTracks[idT].dx = ((float)(markerCenter[idD].x) - vecTracks[idT].preCen.x) / diffDt;
        vecTracks[idT].dy = ((float)(markerCenter[idD].y) - vecTracks[idT].preCen.y) / diffDt;

        v = (returnDis((float)(markerCenter[idD].x), vecTracks[idT].preCen.x, (float)(markerCenter[idD].y), vecTracks[idT].preCen.y)) / diffDt;

        vecTracks[idT].ax = (vecTracks[idT].dx - preDx) / diffDt; // a
        vecTracks[idT].ay = (vecTracks[idT].dy - preDy) / diffDt; // a

        vecTracks[idT].preCen.x = (float)(markerCenter[idD].x);
        vecTracks[idT].preCen.y = (float)(markerCenter[idD].y);
        vecTracks[idT].preCen.z = (float)(markerCenter[idD].z);
        vecTracks[idT].sec = secsCur; //Time update m/s
        vecTracks[idT].speed = v * 3.6;

        // cout<<"speed : " << vecTracks[idT].speed<<endl;

        vecTracks[idT].clusCen.x = vecTracks[idT].kf.statePost.at<float>(0);
        vecTracks[idT].clusCen.y = vecTracks[idT].kf.statePost.at<float>(1);

        vecTracks[idT].age++;
        vecTracks[idT].cntTotalVisible++;
        vecTracks[idT].cntConsecutiveInvisible = 0;
    }
}

/*
할당되지 않은 각 트랙을 보이지 않는 것으로 표시하고 나이를 1 씩 늘립니다.
*/
void unassignedTracksUpdate()
{
    for (int i = 0; i < (int)vecUnssignedTracks.size(); i++)
    {
        int id = vecUnssignedTracks[i];
        vecTracks[i].age++;
        vecTracks[i].cntConsecutiveInvisible++;
    }
}
void deleteLostTraks()
{
    if ((int)vecTracks.size() == 0)
    {
        return;
    }
    for (int i = 0; i < (int)vecTracks.size(); i++)
    {
        if (vecTracks[i].cntConsecutiveInvisible >= m_thres_invisibleCnt)
        {
            vecTracks.erase(vecTracks.begin() + i);
            i--;
        }
    }
}
void configureKalmanFilter(trackingStruct &track)
{
    KalmanFilter &KF = track.kf;
    // KF
    KF.init(stateVariableDim, stateMeasureDim);

    m_matTransition.copyTo(KF.transitionMatrix);   //A
    m_matMeasurement.copyTo(KF.measurementMatrix); //H

    m_matProcessNoiseCov.copyTo(KF.processNoiseCov);     //Q
    m_matMeasureNoiseCov.copyTo(KF.measurementNoiseCov); //R

    Mat tempCov(stateVariableDim, 1, CV_32FC1, 1);
    KF.errorCovPost = Mat::diag(tempCov);

    KF.statePost.at<float>(0) = track.clusCen.x;
    KF.statePost.at<float>(1) = track.clusCen.y;
    KF.statePost.at<float>(2) = track.dx;
    KF.statePost.at<float>(3) = track.dy;
}
void createNewTraks(const vector<geometry_msgs::Point> &markerCenter)
{
    for (int i = 0; i < (int)vecUnssignedDetections.size(); i++)
    {
        int j = vecUnssignedDetections[i];

        trackingStruct ts;
        // ts.markerBB = markerDetectBB[j];
        // ts.markerCenter = Point2f((markerDetectBB[j].br() + markerDetectBB[j].tl()) / 2);

        ts.clusCen.x = markerCenter[j].x;
        ts.clusCen.y = markerCenter[j].y;
        ts.clusCen.z = markerCenter[j].z;

        ts.preCen.x = markerCenter[j].x;
        ts.preCen.y = markerCenter[j].y;
        ts.preCen.z = markerCenter[j].z;
        ts.age = 1;
        ts.cntTotalVisible = 1;
        ts.cntConsecutiveInvisible = 0;
        ts.id = nextID++;
        ts.dx = 0;
        ts.dy = 0;
        ts.dz = 0;
        // ts.ax = 0;
        // ts.ay = 0;
        // ts.az = 0;

        configureKalmanFilter(ts);
        vecTracks.push_back(ts);
    }
}

void make_marker(geometry_msgs::Point cent, int nId, float speed)
{
    //width, heimake_markerght, xmin,ymin,score,labels
    /**********************************
                                 
               Marker            
                                 
  **********************************/
    float center_x = cent.x;
    float center_y = cent.y;
    float center_z = cent.z;
    int classification = 0;

    visualization_msgs::Marker cluster_marker;
    cluster_marker.header.stamp = ros::Time::now();
    cluster_marker.header.frame_id = "/os1_lidar";
    cluster_marker.ns = "marker";

    cluster_marker.id = nId;

    cluster_marker.action = visualization_msgs::Marker::ADD;
    cluster_marker.type = visualization_msgs::Marker::CUBE;
    cluster_marker.lifetime = ros::Duration(0.1);

    cluster_marker.pose.position.x = center_x;
    cluster_marker.pose.position.y = center_y;
    cluster_marker.pose.position.z = 0.5;
    cluster_marker.pose.orientation.w = 1.0;
    if (center_z == 2) //Car
    {
        cluster_marker.color.r = 0.0;
        cluster_marker.color.g = 0.0;
        cluster_marker.color.b = 1.0;

        cluster_marker.scale.x = 4.6;
        cluster_marker.scale.y = 1.8;
        cluster_marker.scale.z = 1.477;
    }
    else if (center_z == 4) //Bus
    {
        cluster_marker.color.r = 0.0;
        cluster_marker.color.g = 1.0;
        cluster_marker.color.b = 0.0;

        cluster_marker.scale.x = 9.0;
        cluster_marker.scale.y = 2.5;
        cluster_marker.scale.z = 3.2;
    }

    cluster_marker.color.a = 1.0;

    tracking_marker_array.markers.push_back(cluster_marker);
    
    cluster_marker.type = visualization_msgs::Marker::TEXT_VIEW_FACING;

    cluster_marker.color.r = 1.0;
    cluster_marker.color.g = 1.0;
    cluster_marker.color.b = 1.0;
    cluster_marker.color.a = 1.0;
    cluster_marker.scale.z = 1.0;
    char buf[100];
    float distance = (float)(sqrt(pow(center_x, 2) + pow(center_y, 2)));

    if (center_z == 2)
    {
        sprintf(buf, "Car ID : %d Distance : %2.2fM Speed : %f", nId, distance, speed);
    }
    if (center_z == 4)
    {
        sprintf(buf, "Bus ID : %d Distance : %2.2fM Speed : %f", nId, distance, speed);
    }


    cluster_marker.text = buf;
    tracking_text_array.markers.push_back(cluster_marker);
}

void displayTrack()
{
    int minVisibleCount = 8;
    
    tracking_marker_array.markers.clear();
    tracking_text_array.markers.clear();
    for (auto i : vecTracks)
    {
        geometry_msgs::Point cent;

        
        cent.x = i.clusCen.x;
        cent.y = i.clusCen.y;
        cent.z = i.clusCen.z;
        make_marker(cent, i.id, i.speed);
    }
    pub_tracking_box.publish(tracking_marker_array);
    pub_tracking_txt.publish(tracking_text_array);
    

}

void msgCallback(const visualization_msgs::MarkerArray &msg)
{
    markerCenter.clear();
    for (auto i : msg.markers)
    {
        geometry_msgs::Point obj;

        obj.x = i.pose.position.x;
        obj.y = i.pose.position.y;
        
        if(i.ns == "Car")
        {
            obj.z = 2;
        }
        else if(i.ns == "Bus")
        {
            obj.z = 4;
        }
        // obj.z = i.ns;

        markerCenter.push_back(obj);
    }

    //Tracking part
    {

        predictNewLocationOfTracks();

        assignDetectionsTracks(markerCenter);

        assignedTracksUpdate(markerCenter);

        unassignedTracksUpdate();

        deleteLostTraks();

        createNewTraks(markerCenter);

        displayTrack();
    }
}

int main(int argc, char **argv)
{

    ros::init(argc, argv, "classification_node");

    ros::NodeHandle nh;
    sub_classification_result = nh.subscribe("lidar_cnn_maker", 1, msgCallback);
    pub_tracking_box = nh.advertise<visualization_msgs::MarkerArray>("/tracking_box", 1);
    pub_tracking_txt = nh.advertise<visualization_msgs::MarkerArray>("/tracking_txt", 1);

    ros::spin();

    return 0;
}
