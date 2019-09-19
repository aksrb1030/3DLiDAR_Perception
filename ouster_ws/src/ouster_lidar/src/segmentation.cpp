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
#include "geometry_msgs/PolygonStamped.h"
#include "geometry_msgs/Polygon.h"
#include <jsk_recognition_msgs/PolygonArray.h>

#include <image_transport/image_transport.h>
#include <sensor_msgs/image_encodings.h>
#include <sensor_msgs/Image.h>
#include <visualization_msgs/Marker.h>
#include <visualization_msgs/MarkerArray.h>
#include <tf/transform_datatypes.h>

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

using namespace sensor_msgs::image_encodings;
using namespace std;

ros::Subscriber sub_ground_removed;
ros::Publisher pub_segmentation;
ros::Publisher pub_segmentation_intensity;
ros::Publisher pub_segmentation_result;
ros::Publisher pub_poly;

geometry_msgs::PolygonStamped polygonViewer(pcl::PointCloud<pcl::PointXYZI> current_cluster,float min_z,float max_z, ros::Time time)
{
  std::vector<cv::Point2f> points;
  geometry_msgs::PolygonStamped poly;
  std::vector<cv::Point2f> hull;
  poly.header.frame_id="/os1_lidar";

  poly.header.stamp = time;

  for (int i=0; i<current_cluster.points.size(); i++)
    {
      cv::Point2f pt;
      pt.x = current_cluster.points[i].x;
      pt.y = current_cluster.points[i].y;
      points.push_back(pt);
    }

  cv::convexHull(points, hull);
  
  for (size_t i = 0; i< hull.size() + 1 ; i++)
  {
    geometry_msgs::Point32 point;
    point.x = hull[i%hull.size()].x;
    point.y = hull[i%hull.size()].y;
    point.z = min_z;
    poly.polygon.points.push_back(point);
  }

  for (size_t i = 0; i< hull.size() + 1 ; i++)
  {
    geometry_msgs::Point32 point;
    point.x = hull[i%hull.size()].x;
    point.y = hull[i%hull.size()].y;
    point.z = max_z;
    poly.polygon.points.push_back(point);
  }
  return poly;
}

void msgCallback(const sensor_msgs::PointCloud2ConstPtr& msg) {
  /*******************************
  **                            **
  **         Save time      
    **
  **                            **
  *******************************/
  ros::Time time = ros::Time::now();
  /**********************************
  **                               **
  **         Segmentation          **
  **                               **
  **********************************/
  pcl::PointCloud<pcl::PointXYZI> ece_cluster;
  pcl::fromROSMsg(*msg, ece_cluster);
  /********************************************************
  **                                                     **
  **      Downsampling using a VoxelGrid filter          **
  **                                                     **
  ********************************************************/
  pcl::VoxelGrid<pcl::PointXYZI> vg;
  pcl::PointCloud<pcl::PointXYZI>::Ptr cloud_filtered(new pcl::PointCloud<pcl::PointXYZI>);

  vg.setInputCloud(ece_cluster.makeShared());
  vg.setLeafSize(0.4f, 0.4f, 0.01f); // 0.01f is 1cm
  vg.filter(*cloud_filtered);

  /**********************************
  **                               **
  **          Clustering           **
  **                               **
  **********************************/
  pcl::search::KdTree<pcl::PointXYZI>::Ptr tree(new pcl::search::KdTree<pcl::PointXYZI>);

  tree->setInputCloud(cloud_filtered);
  std::vector<pcl::PointIndices> cluster_indices;
  pcl::EuclideanClusterExtraction<pcl::PointXYZI> ec;
  ec.setClusterTolerance(0.75); //(0.02) -> 2cm
  ec.setMinClusterSize(10); 
  ec.setMaxClusterSize(1000);
  ec.setSearchMethod(tree);
  ec.setInputCloud(cloud_filtered);
  ec.extract(cluster_indices);


  pcl::PointCloud<pcl::PointXYZI> cloud_cluster;
  pcl::PointCloud<pcl::PointXYZI> cloud_cluster2;
  jsk_recognition_msgs::PolygonArray polyarr;

  int j = 0;

  ouster_lidar::MarkerWithCloudArray marker_with_cloud_array;

  for (std::vector<pcl::PointIndices>::const_iterator it = cluster_indices.begin(); it != cluster_indices.end(); ++it) 
  {
    /************************************************
    **                                             **
    **      Calculate each clustered cloud         **
    **                                             **
    ************************************************/
    float max_x = -100;
    float max_y = -100;
    float max_z = -100;
    float min_x = 100;
    float min_y = 100;
    float min_z = 100;

    pcl::PointCloud<pcl::PointXYZI> single_cloud_cluster;
    
    for (std::vector<int>::const_iterator pit = it->indices.begin(); pit != it->indices.end(); ++pit) 
    {
      /************************************************
      **                                             **
      **                Min / Max Box                **
      **                                             **
      ************************************************/
      if(max_x < cloud_filtered->points[*pit].x)
        max_x = cloud_filtered->points[*pit].x;
      
      if(max_y < cloud_filtered->points[*pit].y)
        max_y = cloud_filtered->points[*pit].y;
      
      if(max_z < cloud_filtered->points[*pit].z)
        max_z = cloud_filtered->points[*pit].z;
      
      if(min_x > cloud_filtered->points[*pit].x)
        min_x = cloud_filtered->points[*pit].x;
      
      if(min_y > cloud_filtered->points[*pit].y)
        min_y = cloud_filtered->points[*pit].y;
      
      if(min_z > cloud_filtered->points[*pit].z)
        min_z = cloud_filtered->points[*pit].z;
      /************************************************
      **                                             **
      **     Inject color into clustered cloud       **
      **                                             **
      ************************************************/
      pcl::PointXYZI pt = cloud_filtered->points[*pit];
      pcl::PointXYZI pt2;
      pcl::PointXYZI pt3;

      pt2.x = pt.x, pt2.y = pt.y, pt2.z = pt.z, pt2.intensity = pt.intensity;
      pt3.x = pt.x, pt3.y = pt.y, pt3.z = pt.z;
      pt3.intensity = (float)(j + 1);

      cloud_cluster.push_back(pt2);
      cloud_cluster2.push_back(pt3);
      single_cloud_cluster.push_back(pt2);       
    }
    polyarr.header.stamp = time;
    polyarr.header.frame_id = "/os1_lidar";
    polyarr.polygons.push_back(polygonViewer(single_cloud_cluster,min_z, max_z, time));
    
    /******************************
    **                           **
    **     Make each marker      **
    **                           **
    ******************************/
    visualization_msgs::Marker min_max_marker;

    min_max_marker.header.stamp = time;
    min_max_marker.header.frame_id = "/os1_lidar";
    min_max_marker.ns = "marker";
    min_max_marker.id = j + 1;

    min_max_marker.action = visualization_msgs::Marker::ADD;
    min_max_marker.type = visualization_msgs::Marker::CUBE;
    min_max_marker.lifetime = ros::Duration(0.15);

    min_max_marker.pose.position.x = (min_x + max_x) / 2;
    min_max_marker.pose.position.y = (min_y + max_y) / 2;
    min_max_marker.pose.position.z = (min_z + max_z) / 2;
    min_max_marker.pose.orientation.w = 1.0;

    min_max_marker.color.r = 0.0;
    min_max_marker.color.g = 1.0;
    min_max_marker.color.b = 0.0;
    min_max_marker.color.a = 0.5;

    min_max_marker.scale.x = max_x - min_x;
    min_max_marker.scale.y = max_y - min_y;
    min_max_marker.scale.z = max_z - min_z;

    j++;
    /*****************************************************
    **                                                  **
    **     Put marker and each pointcloud in array      **
    **                                                  **
    *****************************************************/
    ouster_lidar::MarkerWithCloud marker_with_cloud;
    marker_with_cloud.marker = min_max_marker;

    pcl::PCLPointCloud2 cloud_s;
    pcl::PCLPointCloud2 cloud_s2;
    pcl::toPCLPointCloud2(single_cloud_cluster, cloud_s);

    sensor_msgs::PointCloud2 output_s;
    pcl_conversions::fromPCL(cloud_s, output_s);

    output_s.header.stamp = time;
    output_s.header.frame_id = "/os1_lidar";

    marker_with_cloud.pointcloud = output_s;
    marker_with_cloud_array.array.push_back(marker_with_cloud);
    
  }
  /*******************************************************
    **                                                    **
    **                 Publish poly msg                   **
    **                                                    **
    *******************************************************/
  pub_poly.publish(polyarr);

  pcl::PCLPointCloud2 cloud_p;
  pcl::PCLPointCloud2 cloud_p2;
  pcl::toPCLPointCloud2(cloud_cluster, cloud_p);
  pcl::toPCLPointCloud2(cloud_cluster2, cloud_p2);

  sensor_msgs::PointCloud2 output;
  sensor_msgs::PointCloud2 output2;
  pcl_conversions::fromPCL(cloud_p, output);
  pcl_conversions::fromPCL(cloud_p2, output2);

  output.header.stamp = time;
  output.header.frame_id = "/os1_lidar";

  output2.header.stamp = time;
  output2.header.frame_id = "/os1_lidar";

  

  
  

  /*******************************************************
  **                                                    **
  **     Publish clouds and boxes using custom msg      **
  **                                                    **
  *******************************************************/
  pub_segmentation_result.publish(marker_with_cloud_array);
  /*******************************************
  **                                        **
  **     Publish clouds after clustering    **
  **                                        **
  *******************************************/
  pub_segmentation.publish(output);
  pub_segmentation_intensity.publish(output2);
}



int main(int argc, char **argv) {

  ros::init(argc, argv, "segmentation_node");

  ros::NodeHandle nh;
  sub_ground_removed = nh.subscribe("/ground_removed", 1, msgCallback);
  pub_segmentation_result = nh.advertise<ouster_lidar::MarkerWithCloudArray>("/segmentation_result", 1);
  pub_segmentation = nh.advertise<sensor_msgs::PointCloud2>("/segmentation", 1);
  pub_segmentation_intensity = nh.advertise<sensor_msgs::PointCloud2>("/segmentation_intensity", 1);
  pub_poly = nh.advertise<jsk_recognition_msgs::PolygonArray>("/poly_arr",1);
  ros::spin();

  return 0;
}
