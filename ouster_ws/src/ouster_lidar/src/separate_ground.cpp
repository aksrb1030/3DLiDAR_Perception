#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <cv_bridge/cv_bridge.h>

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

ros::Subscriber sub_raw;
ros::Publisher pub_ground_removed;
ros::Publisher pub_ground;
ros::Publisher pub_ground_line;

visualization_msgs::MarkerArray cut_road_array;

#define PLUS_X 30.0
#define MINUS_X -20.0
#define PLUS_Y 8.0
#define MINUS_Y -8.0

#define PLUS_Z 2.0
#define MINUS_Z -1.6

void display_cutroad()
{
  /**********************************
                                 
               Marker            
                                 
  **********************************/
  visualization_msgs::Marker ground_marker;
  ground_marker.header.stamp = ros::Time::now();
  ground_marker.header.frame_id = "/os1_lidar";
  ground_marker.ns = "marker";

  ground_marker.action = visualization_msgs::Marker::ADD;
  ground_marker.type = visualization_msgs::Marker::CUBE;
  ground_marker.lifetime = ros::Duration(1);

  ground_marker.id = 0;
  ground_marker.pose.position.x = 0;
  ground_marker.pose.position.y = PLUS_Y;
  ground_marker.pose.position.z = 0;
  ground_marker.pose.orientation.w = 1.0;

  ground_marker.color.r = 0.5;
  ground_marker.color.g = 0.5;
  ground_marker.color.b = 0.5;
  ground_marker.color.a = 1.0;

  ground_marker.scale.x = PLUS_X * 2 + 0.5;
  ground_marker.scale.y = 0.5;
  ground_marker.scale.z = 1.0;

  cut_road_array.markers.push_back(ground_marker);

  ground_marker.id = 1;

  ground_marker.pose.position.x = 0;
  ground_marker.pose.position.y = MINUS_Y;
  ground_marker.pose.position.z = 0;
  ground_marker.pose.orientation.w = 1.0;

  ground_marker.scale.x = PLUS_X * 2+ 0.5;
  ground_marker.scale.y = 0.5;
  ground_marker.scale.z = 1.0;

  cut_road_array.markers.push_back(ground_marker);

  ground_marker.id = 2;

  ground_marker.pose.position.x = PLUS_X;
  ground_marker.pose.position.y = 0;
  ground_marker.pose.position.z = 0;
  ground_marker.pose.orientation.w = 1.0;

  ground_marker.scale.x = 0.5;
  ground_marker.scale.y = PLUS_Y * 2+ 0.5;
  ground_marker.scale.z = 1.0;

  cut_road_array.markers.push_back(ground_marker);

  ground_marker.id = 3;

  ground_marker.pose.position.x = MINUS_X;
  ground_marker.pose.position.y = 0;
  ground_marker.pose.position.z = 0;
  ground_marker.pose.orientation.w = 1.0;

  ground_marker.scale.x = 0.5;
  ground_marker.scale.y = PLUS_Y * 2+ 0.5;
  ground_marker.scale.z = 1.0;

  cut_road_array.markers.push_back(ground_marker);

}
void msgCallback(const sensor_msgs::PointCloud2ConstPtr &msg)
{
  /**********************************
  **                               **
  **         Ground Remove         **
  **                               **
  **********************************/
  pcl::PointCloud<pcl::PointXYZI> laserCloudIn;

  pcl::fromROSMsg(*msg, laserCloudIn);

  pcl::PointCloud<pcl::PointXYZI> laserCloudTop;
  laserCloudTop.header.frame_id = "/os1_lidar";

  pcl::PointCloud<pcl::PointXYZI> laserCloudGround;
  laserCloudGround.header.frame_id = "/os1_lidar";

  int cloudSize = laserCloudIn.points.size();
  float cloudDistance[cloudSize];
  int distance = 0;

  float ground_removed_threshold = -1.4;
  for (int i = 0; i < cloudSize; i++)
  {
    laserCloudIn.points[i].x = -laserCloudIn.points[i].x;
    laserCloudIn.points[i].y = -laserCloudIn.points[i].y;
  }
  for (int i = 0; i < cloudSize; i++)
  {
    if (!std::isnan(laserCloudIn.points[i].x) && !std::isnan(laserCloudIn.points[i].y) && !std::isnan(laserCloudIn.points[i].z) && laserCloudIn.points[i].z < ground_removed_threshold)
    {
      /**********************************
      *                                 *
      *           Ground only           *
      *                                 *
      **********************************/
      laserCloudGround.push_back(laserCloudIn.points[i]);
    }
    else if (!std::isnan(laserCloudIn.points[i].x) && !std::isnan(laserCloudIn.points[i].y) && !std::isnan(laserCloudIn.points[i].z))
    {
      /**********************************
      *                                 *
      *         Ground removed          *
      *                                 *
      **********************************/
      laserCloudTop.push_back(laserCloudIn.points[i]);
      cloudDistance[distance] = std::sqrt(laserCloudIn.points[i].x * laserCloudIn.points[i].x + laserCloudIn.points[i].y * laserCloudIn.points[i].y + laserCloudIn.points[i].z * laserCloudIn.points[i].z);
      distance++;
    }
  }

  /**********************************
  *                                 *
  *           Cut Points            *
  *                                 *
  **********************************/
  sensor_msgs::PointCloud2 groundRemovedCloudOutMsg;
  pcl::toROSMsg(laserCloudTop, groundRemovedCloudOutMsg);
  groundRemovedCloudOutMsg.header.stamp = msg->header.stamp;

  pcl::PCLPointCloud2 cut_cloud;

  pcl::PointCloud<pcl::PointXYZI>::Ptr cloud_1(new pcl::PointCloud<pcl::PointXYZI>);
  pcl::fromROSMsg(groundRemovedCloudOutMsg, *cloud_1);
  pcl::PassThrough<pcl::PointXYZI> pass;
  pass.setInputCloud(cloud_1);

  pass.setFilterFieldName("x");
  pass.setFilterLimits(MINUS_X, PLUS_X);
  pass.filter(*cloud_1);

  pass.setFilterFieldName("y");
  pass.setFilterLimits(MINUS_Y, PLUS_Y);
  pass.filter(*cloud_1);

  pass.setFilterFieldName("z");
  pass.setFilterLimits(MINUS_Z, PLUS_Z);
  pass.filter(*cloud_1);

  pcl::toPCLPointCloud2(*cloud_1, cut_cloud);
  pub_ground_removed.publish(cut_cloud);

  cut_road_array.markers.clear();
  display_cutroad();
  pub_ground_line.publish(cut_road_array);

  sensor_msgs::PointCloud2 groundOnlyCloudOutMsg;
  pcl::toROSMsg(laserCloudGround, groundOnlyCloudOutMsg);
  groundOnlyCloudOutMsg.header.stamp = msg->header.stamp;
  pub_ground.publish(groundOnlyCloudOutMsg);
  
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "separate_ground_node");

  ros::NodeHandle nh;
  sub_raw = nh.subscribe("/os1_cloud_node/points", 1, msgCallback);
  pub_ground_removed = nh.advertise<sensor_msgs::PointCloud2>("/ground_removed", 1);
  pub_ground = nh.advertise<sensor_msgs::PointCloud2>("/ground", 1);
  pub_ground_line = nh.advertise<visualization_msgs::MarkerArray>("/ground_line", 1);
  ros::spin();

  return 0;
}
