#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/video/tracking.hpp"
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

#include <image_transport/image_transport.h>
#include <sensor_msgs/image_encodings.h>
#include <sensor_msgs/Image.h>
#include <visualization_msgs/Marker.h>
#include <visualization_msgs/MarkerArray.h>
#include <sensor_msgs/PointField.h>
#include <sensor_msgs/PointCloud2.h>
#include <ouster_lidar/MarkerWithCloud.h>
#include <ouster_lidar/MarkerWithCloudArray.h>
#include <ouster_lidar/MarkerClassification.h>

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

ros::Subscriber sub_stamp;
ros::Subscriber sub_segmentation_result;

ros::Publisher pub_classification_box;
ros::Publisher pub_classification_txt;
ros::Publisher pub_classification_msg;
std_msgs::Header stamp_time;

visualization_msgs::MarkerArray vehicle_marker_array_global;
visualization_msgs::MarkerArray vehicle_text_array_global;
ouster_lidar::MarkerClassification class_marker_array;
int num = 0;

int filter_pos_x_pos_y[23][9] = {{-2, -2, -2, -2, -2, -2, -2, +2, +2},
                                 {-2, -2, -2, -2, -2, -2, -2, +2, +2},
                                 {-2, -2, -1, -1, -1, -1, -1, +2, +2},
                                 {-2, -2, -1, -1, -1, -1, -1, +2, +2},
                                 {-2, -2, -1, -1, -1, -1, -1, +2, +2},
                                 {-2, -2, -1, -1, -1, -1, -1, +2, +2},
                                 {-2, -2, -1, -1, -1, -1, -1, +2, +2},
                                 {-2, -2, -1, -1, -1, -1, -1, +2, +2},
                                 {-2, -2, -1, -1, -1, -1, -1, +2, +2},
                                 {-2, -2, -1, -1, -1, -1, -1, +2, +2},
                                 {-2, -2, -1, -1, -1, -1, -1, +2, +2},
                                 {-2, -2, -1, -1, -1, -1, -1, +2, +2},
                                 {+2, +2, -0, -0, -0, -0, -0, +2, +2},
                                 {+2, +2, -0, -0, -0, -0, -0, +2, +2},
                                 {+2, +2, -0, -0, -0, -0, -0, +2, +2},
                                 {+2, +2, -0, -0, -0, -0, -0, +2, +2},
                                 {+2, +2, -0, -0, -0, -0, -0, +2, +2},
                                 {+2, +2, -0, -0, -0, -0, -0, +2, +2},
                                 {+2, +2, -0, -0, -0, -0, -0, +2, +2},
                                 {+2, +2, -0, -0, -0, -0, -0, +2, +2},
                                 {+2, +2, -0, -0, -0, -0, -0, +2, +2},
                                 {+2, +2, +2, +2, +2, +2, +2, +2, +2},
                                 {+2, +2, +2, +2, +2, +2, +2, +2, +2}};

int filter_pos_x_neg_y[23][9] = {{+2, +2, -2, -2, -2, -2, -2, -2, -2},
                                 {+2, +2, -2, -2, -2, -2, -2, -2, -2},
                                 {+2, +2, -1, -1, -1, -1, -1, -2, -2},
                                 {+2, +2, -1, -1, -1, -1, -1, -2, -2},
                                 {+2, +2, -1, -1, -1, -1, -1, -2, -2},
                                 {+2, +2, -1, -1, -1, -1, -1, -2, -2},
                                 {+2, +2, -1, -1, -1, -1, -1, -2, -2},
                                 {+2, +2, -1, -1, -1, -1, -1, -2, -2},
                                 {+2, +2, -1, -1, -1, -1, -1, -2, -2},
                                 {+2, +2, -1, -1, -1, -1, -1, -2, -2},
                                 {+2, +2, -1, -1, -1, -1, -1, -2, -2},
                                 {+2, +2, -1, -1, -1, -1, -1, -2, -2},
                                 {+2, +2, -0, -0, -0, -0, -0, +2, +2},
                                 {+2, +2, -0, -0, -0, -0, -0, +2, +2},
                                 {+2, +2, -0, -0, -0, -0, -0, +2, +2},
                                 {+2, +2, -0, -0, -0, -0, -0, +2, +2},
                                 {+2, +2, -0, -0, -0, -0, -0, +2, +2},
                                 {+2, +2, -0, -0, -0, -0, -0, +2, +2},
                                 {+2, +2, -0, -0, -0, -0, -0, +2, +2},
                                 {+2, +2, -0, -0, -0, -0, -0, +2, +2},
                                 {+2, +2, -0, -0, -0, -0, -0, +2, +2},
                                 {+2, +2, +2, +2, +2, +2, +2, +2, +2},
                                 {+2, +2, +2, +2, +2, +2, +2, +2, +2}};

int filter_neg_x_pos_y[23][9] = {{+2, +2, +2, +2, +2, +2, +2, +2, +2},
                                 {+2, +2, +2, +2, +2, +2, +2, +2, +2},
                                 {+2, +2, -0, -0, -0, -0, -0, +2, +2},
                                 {+2, +2, -0, -0, -0, -0, -0, +2, +2},
                                 {+2, +2, -0, -0, -0, -0, -0, +2, +2},
                                 {+2, +2, -0, -0, -0, -0, -0, +2, +2},
                                 {+2, +2, -0, -0, -0, -0, -0, +2, +2},
                                 {+2, +2, -0, -0, -0, -0, -0, +2, +2},
                                 {+2, +2, -0, -0, -0, -0, -0, +2, +2},
                                 {+2, +2, -0, -0, -0, -0, -0, +2, +2},
                                 {+2, +2, -0, -0, -0, -0, -0, +2, +2},
                                 {-2, -2, -1, -1, -1, -1, -1, +2, +2},
                                 {-2, -2, -1, -1, -1, -1, -1, +2, +2},
                                 {-2, -2, -1, -1, -1, -1, -1, +2, +2},
                                 {-2, -2, -1, -1, -1, -1, -1, +2, +2},
                                 {-2, -2, -1, -1, -1, -1, -1, +2, +2},
                                 {-2, -2, -1, -1, -1, -1, -1, +2, +2},
                                 {-2, -2, -1, -1, -1, -1, -1, +2, +2},
                                 {-2, -2, -1, -1, -1, -1, -1, +2, +2},
                                 {-2, -2, -1, -1, -1, -1, -1, +2, +2},
                                 {-2, -2, -1, -1, -1, -1, -1, +2, +2},
                                 {-2, -2, -2, -2, -2, -2, -2, +2, +2},
                                 {-2, -2, -2, -2, -2, -2, -2, +2, +2}};

int filter_neg_x_neg_y[23][9] = {{+2, +2, +2, +2, +2, +2, +2, +2, +2},
                                 {+2, +2, +2, +2, +2, +2, +2, +2, +2},
                                 {+2, +2, -0, -0, -0, -0, -0, +2, +2},
                                 {+2, +2, -0, -0, -0, -0, -0, +2, +2},
                                 {+2, +2, -0, -0, -0, -0, -0, +2, +2},
                                 {+2, +2, -0, -0, -0, -0, -0, +2, +2},
                                 {+2, +2, -0, -0, -0, -0, -0, +2, +2},
                                 {+2, +2, -0, -0, -0, -0, -0, +2, +2},
                                 {+2, +2, -0, -0, -0, -0, -0, +2, +2},
                                 {+2, +2, -0, -0, -0, -0, -0, +2, +2},
                                 {+2, +2, -0, -0, -0, -0, -0, +2, +2},
                                 {+2, +2, -1, -1, -1, -1, -1, -2, -2},
                                 {+2, +2, -1, -1, -1, -1, -1, -2, -2},
                                 {+2, +2, -1, -1, -1, -1, -1, -2, -2},
                                 {+2, +2, -1, -1, -1, -1, -1, -2, -2},
                                 {+2, +2, -1, -1, -1, -1, -1, -2, -2},
                                 {+2, +2, -1, -1, -1, -1, -1, -2, -2},
                                 {+2, +2, -1, -1, -1, -1, -1, -2, -2},
                                 {+2, +2, -1, -1, -1, -1, -1, -2, -2},
                                 {+2, +2, -1, -1, -1, -1, -1, -2, -2},
                                 {+2, +2, -1, -1, -1, -1, -1, -2, -2},
                                 {+2, +2, -2, -2, -2, -2, -2, -2, -2},
                                 {+2, +2, -2, -2, -2, -2, -2, -2, -2}};

int bus_filter_pos_x_pos_y[45][13] = {{-2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, +2, +2},
                                      {-2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, +2, +2},
                                      {-2, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, +2, +2},
                                      {-2, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, +2, +2},
                                      {-2, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, +2, +2},
                                      {-2, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, +2, +2},
                                      {-2, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, +2, +2},
                                      {-2, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, +2, +2},
                                      {-2, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, +2, +2},
                                      {-2, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, +2, +2},
                                      {-2, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, +2, +2},
                                      {-2, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, +2, +2},
                                      {-2, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, +2, +2},
                                      {-2, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, +2, +2},
                                      {-2, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, +2, +2},
                                      {-2, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, +2, +2},
                                      {-2, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, +2, +2},
                                      {-2, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, +2, +2},
                                      {-2, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, +2, +2},
                                      {-2, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, +2, +2},
                                      {-2, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, +2, +2},
                                      {-2, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, +2, +2},
                                      {-2, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, +2, +2},
                                      {+2, +2, -0, -0, -0, -0, -0, -0, -0, -0, -0, +2, +2},
                                      {+2, +2, -0, -0, -0, -0, -0, -0, -0, -0, -0, +2, +2},
                                      {+2, +2, -0, -0, -0, -0, -0, -0, -0, -0, -0, +2, +2},
                                      {+2, +2, -0, -0, -0, -0, -0, -0, -0, -0, -0, +2, +2},
                                      {+2, +2, -0, -0, -0, -0, -0, -0, -0, -0, -0, +2, +2},
                                      {+2, +2, -0, -0, -0, -0, -0, -0, -0, -0, -0, +2, +2},
                                      {+2, +2, -0, -0, -0, -0, -0, -0, -0, -0, -0, +2, +2},
                                      {+2, +2, -0, -0, -0, -0, -0, -0, -0, -0, -0, +2, +2},
                                      {+2, +2, -0, -0, -0, -0, -0, -0, -0, -0, -0, +2, +2},
                                      {+2, +2, -0, -0, -0, -0, -0, -0, -0, -0, -0, +2, +2},
                                      {+2, +2, -0, -0, -0, -0, -0, -0, -0, -0, -0, +2, +2},
                                      {+2, +2, -0, -0, -0, -0, -0, -0, -0, -0, -0, +2, +2},
                                      {+2, +2, -0, -0, -0, -0, -0, -0, -0, -0, -0, +2, +2},
                                      {+2, +2, -0, -0, -0, -0, -0, -0, -0, -0, -0, +2, +2},
                                      {+2, +2, -0, -0, -0, -0, -0, -0, -0, -0, -0, +2, +2},
                                      {+2, +2, -0, -0, -0, -0, -0, -0, -0, -0, -0, +2, +2},
                                      {+2, +2, -0, -0, -0, -0, -0, -0, -0, -0, -0, +2, +2},
                                      {+2, +2, -0, -0, -0, -0, -0, -0, -0, -0, -0, +2, +2},
                                      {+2, +2, -0, -0, -0, -0, -0, -0, -0, -0, -0, +2, +2},
                                      {+2, +2, -0, -0, -0, -0, -0, -0, -0, -0, -0, +2, +2},
                                      {+2, +2, +2, +2, +2, +2, +2, +2, +2, +2, +2, +2, +2},
                                      {+2, +2, +2, +2, +2, +2, +2, +2, +2, +2, +2, +2, +2}};

int bus_filter_pos_x_neg_y[45][13] = {{+2, +2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2},
                                      {+2, +2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2},
                                      {+2, +2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -2, -2},
                                      {+2, +2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -2, -2},
                                      {+2, +2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -2, -2},
                                      {+2, +2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -2, -2},
                                      {+2, +2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -2, -2},
                                      {+2, +2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -2, -2},
                                      {+2, +2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -2, -2},
                                      {+2, +2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -2, -2},
                                      {+2, +2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -2, -2},
                                      {+2, +2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -2, -2},
                                      {+2, +2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -2, -2},
                                      {+2, +2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -2, -2},
                                      {+2, +2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -2, -2},
                                      {+2, +2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -2, -2},
                                      {+2, +2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -2, -2},
                                      {+2, +2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -2, -2},
                                      {+2, +2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -2, -2},
                                      {+2, +2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -2, -2},
                                      {+2, +2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -2, -2},
                                      {+2, +2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -2, -2},
                                      {+2, +2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -2, -2},
                                      {+2, +2, -0, -0, -0, -0, -0, -0, -0, -0, -0, +2, +2},
                                      {+2, +2, -0, -0, -0, -0, -0, -0, -0, -0, -0, +2, +2},
                                      {+2, +2, -0, -0, -0, -0, -0, -0, -0, -0, -0, +2, +2},
                                      {+2, +2, -0, -0, -0, -0, -0, -0, -0, -0, -0, +2, +2},
                                      {+2, +2, -0, -0, -0, -0, -0, -0, -0, -0, -0, +2, +2},
                                      {+2, +2, -0, -0, -0, -0, -0, -0, -0, -0, -0, +2, +2},
                                      {+2, +2, -0, -0, -0, -0, -0, -0, -0, -0, -0, +2, +2},
                                      {+2, +2, -0, -0, -0, -0, -0, -0, -0, -0, -0, +2, +2},
                                      {+2, +2, -0, -0, -0, -0, -0, -0, -0, -0, -0, +2, +2},
                                      {+2, +2, -0, -0, -0, -0, -0, -0, -0, -0, -0, +2, +2},
                                      {+2, +2, -0, -0, -0, -0, -0, -0, -0, -0, -0, +2, +2},
                                      {+2, +2, -0, -0, -0, -0, -0, -0, -0, -0, -0, +2, +2},
                                      {+2, +2, -0, -0, -0, -0, -0, -0, -0, -0, -0, +2, +2},
                                      {+2, +2, -0, -0, -0, -0, -0, -0, -0, -0, -0, +2, +2},
                                      {+2, +2, -0, -0, -0, -0, -0, -0, -0, -0, -0, +2, +2},
                                      {+2, +2, -0, -0, -0, -0, -0, -0, -0, -0, -0, +2, +2},
                                      {+2, +2, -0, -0, -0, -0, -0, -0, -0, -0, -0, +2, +2},
                                      {+2, +2, -0, -0, -0, -0, -0, -0, -0, -0, -0, +2, +2},
                                      {+2, +2, -0, -0, -0, -0, -0, -0, -0, -0, -0, +2, +2},
                                      {+2, +2, -0, -0, -0, -0, -0, -0, -0, -0, -0, +2, +2},
                                      {+2, +2, +2, +2, +2, +2, +2, +2, +2, +2, +2, +2, +2},
                                      {+2, +2, +2, +2, +2, +2, +2, +2, +2, +2, +2, +2, +2}};

int bus_filter_neg_x_pos_y[45][13] = {{+2, +2, +2, +2, +2, +2, +2, +2, +2, +2, +2, +2, +2},
                                      {+2, +2, +2, +2, +2, +2, +2, +2, +2, +2, +2, +2, +2},
                                      {+2, +2, -0, -0, -0, -0, -0, -0, -0, -0, -0, +2, +2},
                                      {+2, +2, -0, -0, -0, -0, -0, -0, -0, -0, -0, +2, +2},
                                      {+2, +2, -0, -0, -0, -0, -0, -0, -0, -0, -0, +2, +2},
                                      {+2, +2, -0, -0, -0, -0, -0, -0, -0, -0, -0, +2, +2},
                                      {+2, +2, -0, -0, -0, -0, -0, -0, -0, -0, -0, +2, +2},
                                      {+2, +2, -0, -0, -0, -0, -0, -0, -0, -0, -0, +2, +2},
                                      {+2, +2, -0, -0, -0, -0, -0, -0, -0, -0, -0, +2, +2},
                                      {+2, +2, -0, -0, -0, -0, -0, -0, -0, -0, -0, +2, +2},
                                      {+2, +2, -0, -0, -0, -0, -0, -0, -0, -0, -0, +2, +2},
                                      {+2, +2, -0, -0, -0, -0, -0, -0, -0, -0, -0, +2, +2},
                                      {+2, +2, -0, -0, -0, -0, -0, -0, -0, -0, -0, +2, +2},
                                      {+2, +2, -0, -0, -0, -0, -0, -0, -0, -0, -0, +2, +2},
                                      {+2, +2, -0, -0, -0, -0, -0, -0, -0, -0, -0, +2, +2},
                                      {+2, +2, -0, -0, -0, -0, -0, -0, -0, -0, -0, +2, +2},
                                      {+2, +2, -0, -0, -0, -0, -0, -0, -0, -0, -0, +2, +2},
                                      {+2, +2, -0, -0, -0, -0, -0, -0, -0, -0, -0, +2, +2},
                                      {+2, +2, -0, -0, -0, -0, -0, -0, -0, -0, -0, +2, +2},
                                      {+2, +2, -0, -0, -0, -0, -0, -0, -0, -0, -0, +2, +2},
                                      {+2, +2, -0, -0, -0, -0, -0, -0, -0, -0, -0, +2, +2},
                                      {+2, +2, -0, -0, -0, -0, -0, -0, -0, -0, -0, +2, +2},
                                      {-2, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, +2, +2},
                                      {-2, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, +2, +2},
                                      {-2, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, +2, +2},
                                      {-2, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, +2, +2},
                                      {-2, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, +2, +2},
                                      {-2, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, +2, +2},
                                      {-2, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, +2, +2},
                                      {-2, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, +2, +2},
                                      {-2, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, +2, +2},
                                      {-2, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, +2, +2},
                                      {-2, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, +2, +2},
                                      {-2, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, +2, +2},
                                      {-2, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, +2, +2},
                                      {-2, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, +2, +2},
                                      {-2, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, +2, +2},
                                      {-2, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, +2, +2},
                                      {-2, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, +2, +2},
                                      {-2, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, +2, +2},
                                      {-2, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, +2, +2},
                                      {-2, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, +2, +2},
                                      {-2, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, +2, +2},
                                      {-2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, +2, +2},
                                      {-2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, +2, +2}};

int bus_filter_neg_x_neg_y[45][13] = {{+2, +2, +2, +2, +2, +2, +2, +2, +2, +2, +2, +2, +2},
                                      {+2, +2, +2, +2, +2, +2, +2, +2, +2, +2, +2, +2, +2},
                                      {+2, +2, -0, -0, -0, -0, -0, -0, -0, -0, -0, +2, +2},
                                      {+2, +2, -0, -0, -0, -0, -0, -0, -0, -0, -0, +2, +2},
                                      {+2, +2, -0, -0, -0, -0, -0, -0, -0, -0, -0, +2, +2},
                                      {+2, +2, -0, -0, -0, -0, -0, -0, -0, -0, -0, +2, +2},
                                      {+2, +2, -0, -0, -0, -0, -0, -0, -0, -0, -0, +2, +2},
                                      {+2, +2, -0, -0, -0, -0, -0, -0, -0, -0, -0, +2, +2},
                                      {+2, +2, -0, -0, -0, -0, -0, -0, -0, -0, -0, +2, +2},
                                      {+2, +2, -0, -0, -0, -0, -0, -0, -0, -0, -0, +2, +2},
                                      {+2, +2, -0, -0, -0, -0, -0, -0, -0, -0, -0, +2, +2},
                                      {+2, +2, -0, -0, -0, -0, -0, -0, -0, -0, -0, +2, +2},
                                      {+2, +2, -0, -0, -0, -0, -0, -0, -0, -0, -0, +2, +2},
                                      {+2, +2, -0, -0, -0, -0, -0, -0, -0, -0, -0, +2, +2},
                                      {+2, +2, -0, -0, -0, -0, -0, -0, -0, -0, -0, +2, +2},
                                      {+2, +2, -0, -0, -0, -0, -0, -0, -0, -0, -0, +2, +2},
                                      {+2, +2, -0, -0, -0, -0, -0, -0, -0, -0, -0, +2, +2},
                                      {+2, +2, -0, -0, -0, -0, -0, -0, -0, -0, -0, +2, +2},
                                      {+2, +2, -0, -0, -0, -0, -0, -0, -0, -0, -0, +2, +2},
                                      {+2, +2, -0, -0, -0, -0, -0, -0, -0, -0, -0, +2, +2},
                                      {+2, +2, -0, -0, -0, -0, -0, -0, -0, -0, -0, +2, +2},
                                      {+2, +2, -0, -0, -0, -0, -0, -0, -0, -0, -0, +2, +2},
                                      {+2, +2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -2, -2},
                                      {+2, +2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -2, -2},
                                      {+2, +2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -2, -2},
                                      {+2, +2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -2, -2},
                                      {+2, +2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -2, -2},
                                      {+2, +2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -2, -2},
                                      {+2, +2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -2, -2},
                                      {+2, +2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -2, -2},
                                      {+2, +2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -2, -2},
                                      {+2, +2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -2, -2},
                                      {+2, +2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -2, -2},
                                      {+2, +2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -2, -2},
                                      {+2, +2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -2, -2},
                                      {+2, +2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -2, -2},
                                      {+2, +2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -2, -2},
                                      {+2, +2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -2, -2},
                                      {+2, +2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -2, -2},
                                      {+2, +2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -2, -2},
                                      {+2, +2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -2, -2},
                                      {+2, +2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -2, -2},
                                      {+2, +2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -2, -2},
                                      {+2, +2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2},
                                      {+2, +2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2}};

void rosTime(const sensor_msgs::PointCloud2ConstPtr &msg)
{
  stamp_time = msg->header;
}

visualization_msgs::Marker isCar(visualization_msgs::Marker mark, pcl::PointCloud<pcl::PointXYZI> cloud)
{
  /**********************************
  **                               **
  **      Check this is Car        **
  **                               **
  **********************************/
  float fixed_scale_x = 4.6;
  float fixed_scale_y = 1.8;
  float fixed_scale_z = 1.477;

  float fake_x = 0.0;
  float fake_y = 0.0;
  int filter_check = 0;

  if (mark.pose.position.x > 0)
  {
    fake_x = mark.pose.position.x - 0.5 * mark.scale.x + 0.5 * fixed_scale_x;
    if (mark.pose.position.y > 0)
    {
      fake_y = mark.pose.position.y - 0.5 * mark.scale.y + 0.5 * fixed_scale_y;
      filter_check = 1;
    }
    else
    {
      fake_y = mark.pose.position.y + 0.5 * mark.scale.y - 0.5 * fixed_scale_y;
      filter_check = 2;
    }
  }

  else
  {
    fake_x = mark.pose.position.x + 0.5 * mark.scale.x - 0.5 * fixed_scale_x;
    if (mark.pose.position.y > 0)
    {
      fake_y = mark.pose.position.y - 0.5 * mark.scale.y + 0.5 * fixed_scale_y;
      filter_check = 3;
    }
    else
    {
      fake_y = mark.pose.position.y + 0.5 * mark.scale.y - 0.5 * fixed_scale_y;
      filter_check = 4;
    }
  }

  int array[23][9] = {0};

  for (auto point : cloud)
  {
    if ((-100.0 < point.x) && (100.0 > point.x) && (-100.0 < point.y) && (100.0 > point.y))
    {
      if ((fake_x - 0.5 * fixed_scale_x < point.x) && (fake_x + 0.5 * fixed_scale_x > point.x) && (fake_y - 0.5 * fixed_scale_y < point.y) && (fake_y + 0.5 * fixed_scale_y > point.y))
      {
        array[11 - (int)((point.x - fake_x) / 0.2)][4 - (int)((point.y - fake_y) / 0.2)]++;
      }
    }
  }

  cout << "********************************************************" << endl;
  cout << "id : " << mark.id << endl;
  for (int i = 0; i < 23; i++)
  {
    for (int j = 0; j < 9; j++)
    {
      cout << array[i][j] << "\t";
    }
    cout << endl;
  }

  int sum = 0;

  if (filter_check == 1)
  {
    for (int i = 0; i < 23; i++)
    {
      for (int j = 0; j < 9; j++)
      {
        sum += array[i][j] * filter_pos_x_pos_y[i][j];
      }
    }
    cout << sum << endl;
  }

  else if (filter_check == 2)
  {
    for (int i = 0; i < 23; i++)
    {
      for (int j = 0; j < 9; j++)
      {
        sum += array[i][j] * filter_pos_x_neg_y[i][j];
      }
    }
    cout << sum << endl;
  }

  else if (filter_check == 3)
  {
    for (int i = 0; i < 23; i++)
    {
      for (int j = 0; j < 9; j++)
      {
        sum += array[i][j] * filter_neg_x_pos_y[i][j];
      }
    }
    cout << sum << endl;
  }

  else if (filter_check == 4)
  {
    for (int i = 0; i < 23; i++)
    {
      for (int j = 0; j < 9; j++)
      {
        sum += array[i][j] * filter_neg_x_neg_y[i][j];
      }
    }
    cout << sum << endl;
  }

  float threshold = 100;
  float filter_distance = (float)(sqrt(pow(fake_x,2) + pow(fake_y,2)));

  if(filter_distance >= 20)
  {
    threshold = 75;
  }
  if (sum >= threshold)
  {
    mark.pose.position.x = fake_x;
    mark.pose.position.y = fake_y;
    mark.scale.x = fixed_scale_x;
    mark.scale.y = fixed_scale_y;
    mark.scale.z = fixed_scale_z;
    mark.color.r = 0.0;
    mark.color.g = 0.0;
    mark.color.b = 1.0;
    mark.color.a = 1.0;
    mark.ns = "Car";
  }
  else
  {
    mark.pose.position.x = 0.0;
    mark.pose.position.y = 0.0;
    mark.pose.position.z = 0.0;
    mark.scale.x = 0.0;
    mark.scale.y = 0.0;
    mark.scale.z = 0.0;
    mark.color.r = 0.0;
    mark.color.g = 0.0;
    mark.color.b = 0.0;

    mark.ns = "No Car";
  }

  return mark;
}

visualization_msgs::Marker isBus(visualization_msgs::Marker mark, pcl::PointCloud<pcl::PointXYZI> cloud)
{
  /**********************************
  **                               **
  **      Check this is Bus        **
  **                               **
  **********************************/

  float fixed_scale_x = 9.0;
  float fixed_scale_y = 2.6;
  float fixed_scale_z = 3.2;

  float fake_x = 0.0;
  float fake_y = 0.0;
  int filter_check = 0;

  if (mark.pose.position.x > 0)
  {
    fake_x = mark.pose.position.x - 0.5 * mark.scale.x + 0.5 * fixed_scale_x;
    if (mark.pose.position.y > 0)
    {
      fake_y = mark.pose.position.y - 0.5 * mark.scale.y + 0.5 * fixed_scale_y;
      filter_check = 1;
    }
    else
    {
      fake_y = mark.pose.position.y + 0.5 * mark.scale.y - 0.5 * fixed_scale_y;
      filter_check = 2;
    }
  }

  else
  {
    fake_x = mark.pose.position.x + 0.5 * mark.scale.x - 0.5 * fixed_scale_x;
    if (mark.pose.position.y > 0)
    {
      fake_y = mark.pose.position.y - 0.5 * mark.scale.y + 0.5 * fixed_scale_y;
      filter_check = 3;
    }
    else
    {
      fake_y = mark.pose.position.y + 0.5 * mark.scale.y - 0.5 * fixed_scale_y;
      filter_check = 4;
    }
  }

  int array[45][13] = {0};

  for (auto point : cloud)
  {
    if ((-100.0 < point.x) && (100.0 > point.x) && (-100.0 < point.y) && (100.0 > point.y))
    {
      if ((fake_x - 0.5 * fixed_scale_x < point.x) && (fake_x + 0.5 * fixed_scale_x > point.x) && (fake_y - 0.5 * fixed_scale_y < point.y) && (fake_y + 0.5 * fixed_scale_y > point.y))
      {
        array[22 - (int)((point.x - fake_x) / 0.2)][6 - (int)((point.y - fake_y) / 0.2)]++;
      }
    }
  }

  cout << "********************************************************" << endl;
  cout << "id : " << mark.id << endl;
  for (int i = 0; i < 45; i++)
  {
    for (int j = 0; j < 13; j++)
    {
      cout << array[i][j] << "\t";
    }
    cout << endl;
  }
  int sum = 0;

  if (filter_check == 1)
  {
    for (int i = 0; i < 45; i++)
    {
      for (int j = 0; j < 13; j++)
      {
        sum += array[i][j] * bus_filter_pos_x_pos_y[i][j];
      }
    }
    cout << sum << endl;
  }

  else if (filter_check == 2)
  {
    for (int i = 0; i < 45; i++)
    {
      for (int j = 0; j < 13; j++)
      {
        sum += array[i][j] * bus_filter_pos_x_neg_y[i][j];
      }
    }
    cout << sum << endl;
  }

  else if (filter_check == 3)
  {
    for (int i = 0; i < 45; i++)
    {
      for (int j = 0; j < 13; j++)
      {
        sum += array[i][j] * bus_filter_neg_x_pos_y[i][j];
      }
    }
    cout << sum << endl;
  }

  else if (filter_check == 4)
  {
    for (int i = 0; i < 45; i++)
    {
      for (int j = 0; j < 13; j++)
      {
        sum += array[i][j] * bus_filter_neg_x_neg_y[i][j];
      }
    }
    cout << sum << endl;
  }

  float threshold = 100;
  float filter_distance = (float)(sqrt(pow(fake_x,2) + pow(fake_y,2)));

  if(filter_distance >= 20)
  {
    threshold = 75;
  }

  if (sum >= threshold)
  {
    mark.pose.position.x = fake_x;
    mark.pose.position.y = fake_y;
    mark.scale.x = fixed_scale_x;
    mark.scale.y = fixed_scale_y;
    mark.scale.z = fixed_scale_z;
    mark.color.r = 0.0;
    mark.color.g = 1.0;
    mark.color.b = 0.0;
    mark.color.a = 1.0;

    mark.ns = "Bus";
  }
  else
  {
    mark.pose.position.x = 0.0;
    mark.pose.position.y = 0.0;
    mark.pose.position.z = 0.0;
    mark.scale.x = 0.0;
    mark.scale.y = 0.0;
    mark.scale.z = 0.0;
    mark.color.r = 0.0;
    mark.color.g = 0.0;
    mark.color.b = 0.0;
    mark.ns = "No Bus";
  }

  return mark;
}

void msgCallback(ouster_lidar::MarkerWithCloudArray msg)
{

  visualization_msgs::MarkerArray vehicle_marker_array;
  visualization_msgs::MarkerArray vehicle_text_array;

  for (auto i : msg.array)
  {
    /**********************************
    **                               **
    **         Classification        **
    **                               **
    **********************************/
    pcl::PointCloud<pcl::PointXYZI> cloud_from_seg;
    pcl::fromROSMsg(i.pointcloud, cloud_from_seg);

    /****************************************
    **                                     **
    **         First area for vehicle      **
    **                                     **
    ****************************************/
    float condition_area_x = 50.0;
    float condition_obj_z = 1.0;

    if (i.marker.pose.position.z < condition_obj_z)
    {
      if (i.marker.pose.position.x < condition_area_x && i.marker.pose.position.x > -condition_area_x)
      {
        /*********************************************
        **                                          **
        **         Condition for vehicle            **
        **                                          **
        *********************************************/
        float condition_vehicle_x = 13.0;
        float condition_vehicle_y = 5.0;
        float condition_vehicle_z = 2.5;

        if (i.marker.scale.x < condition_vehicle_x && i.marker.scale.y < condition_vehicle_y && i.marker.scale.z < condition_vehicle_z)
        {
          /*********************************************
          **                                          **
          **         Condition for car / bus          **
          **                                          **
          *********************************************/
          float condition_car_x = 5.0;
          float condition_car_y = 3.0;
          float condition_car_z = 1.5;

          if (i.marker.scale.x < condition_car_x && i.marker.scale.y < condition_car_y && i.marker.scale.z < condition_car_z)
          {
            /**************************************
            **                                   **
            **         Candidate of car          **
            **                                   **
            **************************************/
            visualization_msgs::Marker temp_marker = isCar(i.marker, cloud_from_seg);
            if (temp_marker.scale.x != 0.0)
            {
              vehicle_marker_array.markers.push_back(temp_marker);
              class_marker_array.header = stamp_time;
              class_marker_array.array = vehicle_marker_array_global;
              temp_marker.type = visualization_msgs::Marker::TEXT_VIEW_FACING;

              char buf[100];
              float distance = (float)(sqrt(pow(temp_marker.pose.position.x, 2) + pow(temp_marker.pose.position.y, 2)));

              temp_marker.color.r = 1.0;
              temp_marker.color.g = 1.0;
              temp_marker.color.b = 1.0;
              temp_marker.color.a = 1.0;
              temp_marker.scale.z = 1.0;
              sprintf(buf, "Car ID : %d %f", num, distance);
              temp_marker.text = buf;

              vehicle_text_array.markers.push_back(temp_marker);
            }
            num++;
          }

          else
          {
            /**************************************
            **                                   **
            **         Candidate of bus          **
            **                                   **
            **************************************/
            if (i.marker.pose.position.y < 15.0 && i.marker.pose.position.y > -15.0)
            {
              visualization_msgs::Marker temp_marker = isBus(i.marker, cloud_from_seg);
              if (temp_marker.scale.x != 0.0)
              {
                vehicle_marker_array.markers.push_back(temp_marker);
                class_marker_array.header = stamp_time;
                class_marker_array.array = vehicle_marker_array;
                temp_marker.type = visualization_msgs::Marker::TEXT_VIEW_FACING;
                char buf[100];
                float distance = (float)(sqrt(pow(temp_marker.pose.position.x, 2) + pow(temp_marker.pose.position.y, 2)));
                temp_marker.color.r = 1.0;
                temp_marker.color.g = 1.0;
                temp_marker.color.b = 1.0;
                temp_marker.color.a = 1.0;
                temp_marker.scale.z = 1.0;


                sprintf(buf, "Bus ID : %d %f", num, distance);
                temp_marker.text = buf;

                vehicle_text_array.markers.push_back(temp_marker);
              }
              num++;
            }
          }
        }
      }
      /****************************************
      **                                     **
      **        Second area for vehicle      **
      **                                     **
      ****************************************/
      else
      {
      }
    }
  }
  vehicle_marker_array_global = vehicle_marker_array;
  vehicle_text_array_global = vehicle_text_array;
  class_marker_array.header = stamp_time;
  class_marker_array.array = vehicle_marker_array;
}

int main(int argc, char **argv)
{

  ros::init(argc, argv, "classification_node");

  ros::NodeHandle nh;
  sub_stamp = nh.subscribe("/os1_cloud_node/points", 1, rosTime);
  sub_segmentation_result = nh.subscribe("/segmentation_result", 1, msgCallback);
  pub_classification_box = nh.advertise<visualization_msgs::MarkerArray>("/classification_box", 1);
  pub_classification_txt = nh.advertise<visualization_msgs::MarkerArray>("/classification_txt", 1);
  pub_classification_msg = nh.advertise<ouster_lidar::MarkerClassification>("/classification_msg", 1);

  ros::Time start_time = ros::Time::now();
  ros::Duration timeout(0.01);

  while (ros::ok())
  {
    if (ros::Time::now() - start_time > timeout)
    {
      pub_classification_box.publish(vehicle_marker_array_global);
      pub_classification_txt.publish(vehicle_text_array_global);
      pub_classification_msg.publish(class_marker_array);
      start_time = ros::Time::now();
    }
    ros::spinOnce();
  }

  ros::spin();

  return 0;
}