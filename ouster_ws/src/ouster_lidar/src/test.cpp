
#include <ros/ros.h>

#include <sensor_msgs/PointField.h>
#include <sensor_msgs/PointCloud2.h>

#include <std_msgs/Header.h>

ros::Publisher pub_test;
ros::Subscriber sub_test;

void test(const sensor_msgs::PointCloud2ConstPtr &msg)
{
  sensor_msgs::PointCloud2 only_ground_msg;
  std_msgs::Header newheader;
  newheader.stamp = ros::Time::now();
  sensor_msgs::PointCloud2 lidar_msg;
  lidar_msg.header = newheader;
  pub_test.publish(lidar_msg);
}

int main(int argc, char **argv) {

  ros::init(argc, argv, "lidar_return");

  ros::NodeHandle nh;
  sub_test = nh.subscribe("/os1_cloud_node/points", 1, test);
  pub_test = nh.advertise<sensor_msgs::PointCloud2>("/only_ground", 1);
  
  ros::spin();

  return 0;
}
