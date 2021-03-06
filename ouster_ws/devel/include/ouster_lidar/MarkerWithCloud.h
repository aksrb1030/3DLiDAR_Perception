// Generated by gencpp from file ouster_lidar/MarkerWithCloud.msg
// DO NOT EDIT!


#ifndef OUSTER_LIDAR_MESSAGE_MARKERWITHCLOUD_H
#define OUSTER_LIDAR_MESSAGE_MARKERWITHCLOUD_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <visualization_msgs/Marker.h>
#include <sensor_msgs/PointCloud2.h>

namespace ouster_lidar
{
template <class ContainerAllocator>
struct MarkerWithCloud_
{
  typedef MarkerWithCloud_<ContainerAllocator> Type;

  MarkerWithCloud_()
    : marker()
    , pointcloud()  {
    }
  MarkerWithCloud_(const ContainerAllocator& _alloc)
    : marker(_alloc)
    , pointcloud(_alloc)  {
  (void)_alloc;
    }



   typedef  ::visualization_msgs::Marker_<ContainerAllocator>  _marker_type;
  _marker_type marker;

   typedef  ::sensor_msgs::PointCloud2_<ContainerAllocator>  _pointcloud_type;
  _pointcloud_type pointcloud;





  typedef boost::shared_ptr< ::ouster_lidar::MarkerWithCloud_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::ouster_lidar::MarkerWithCloud_<ContainerAllocator> const> ConstPtr;

}; // struct MarkerWithCloud_

typedef ::ouster_lidar::MarkerWithCloud_<std::allocator<void> > MarkerWithCloud;

typedef boost::shared_ptr< ::ouster_lidar::MarkerWithCloud > MarkerWithCloudPtr;
typedef boost::shared_ptr< ::ouster_lidar::MarkerWithCloud const> MarkerWithCloudConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::ouster_lidar::MarkerWithCloud_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::ouster_lidar::MarkerWithCloud_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace ouster_lidar

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': False}
// {'sensor_msgs': ['/opt/ros/kinetic/share/sensor_msgs/cmake/../msg'], 'geometry_msgs': ['/opt/ros/kinetic/share/geometry_msgs/cmake/../msg'], 'visualization_msgs': ['/opt/ros/kinetic/share/visualization_msgs/cmake/../msg'], 'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg'], 'ouster_lidar': ['/home/bae/ouster_ws/src/ouster_lidar/msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::ouster_lidar::MarkerWithCloud_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::ouster_lidar::MarkerWithCloud_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::ouster_lidar::MarkerWithCloud_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::ouster_lidar::MarkerWithCloud_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::ouster_lidar::MarkerWithCloud_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::ouster_lidar::MarkerWithCloud_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::ouster_lidar::MarkerWithCloud_<ContainerAllocator> >
{
  static const char* value()
  {
    return "dc87fb6525a4fe8bb5f3b24b63ac4895";
  }

  static const char* value(const ::ouster_lidar::MarkerWithCloud_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xdc87fb6525a4fe8bULL;
  static const uint64_t static_value2 = 0xb5f3b24b63ac4895ULL;
};

template<class ContainerAllocator>
struct DataType< ::ouster_lidar::MarkerWithCloud_<ContainerAllocator> >
{
  static const char* value()
  {
    return "ouster_lidar/MarkerWithCloud";
  }

  static const char* value(const ::ouster_lidar::MarkerWithCloud_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::ouster_lidar::MarkerWithCloud_<ContainerAllocator> >
{
  static const char* value()
  {
    return "visualization_msgs/Marker marker\n\
sensor_msgs/PointCloud2 pointcloud\n\
\n\
================================================================================\n\
MSG: visualization_msgs/Marker\n\
# See http://www.ros.org/wiki/rviz/DisplayTypes/Marker and http://www.ros.org/wiki/rviz/Tutorials/Markers%3A%20Basic%20Shapes for more information on using this message with rviz\n\
\n\
uint8 ARROW=0\n\
uint8 CUBE=1\n\
uint8 SPHERE=2\n\
uint8 CYLINDER=3\n\
uint8 LINE_STRIP=4\n\
uint8 LINE_LIST=5\n\
uint8 CUBE_LIST=6\n\
uint8 SPHERE_LIST=7\n\
uint8 POINTS=8\n\
uint8 TEXT_VIEW_FACING=9\n\
uint8 MESH_RESOURCE=10\n\
uint8 TRIANGLE_LIST=11\n\
\n\
uint8 ADD=0\n\
uint8 MODIFY=0\n\
uint8 DELETE=2\n\
uint8 DELETEALL=3\n\
\n\
Header header                        # header for time/frame information\n\
string ns                            # Namespace to place this object in... used in conjunction with id to create a unique name for the object\n\
int32 id 		                         # object ID useful in conjunction with the namespace for manipulating and deleting the object later\n\
int32 type 		                       # Type of object\n\
int32 action 	                       # 0 add/modify an object, 1 (deprecated), 2 deletes an object, 3 deletes all objects\n\
geometry_msgs/Pose pose                 # Pose of the object\n\
geometry_msgs/Vector3 scale             # Scale of the object 1,1,1 means default (usually 1 meter square)\n\
std_msgs/ColorRGBA color             # Color [0.0-1.0]\n\
duration lifetime                    # How long the object should last before being automatically deleted.  0 means forever\n\
bool frame_locked                    # If this marker should be frame-locked, i.e. retransformed into its frame every timestep\n\
\n\
#Only used if the type specified has some use for them (eg. POINTS, LINE_STRIP, ...)\n\
geometry_msgs/Point[] points\n\
#Only used if the type specified has some use for them (eg. POINTS, LINE_STRIP, ...)\n\
#number of colors must either be 0 or equal to the number of points\n\
#NOTE: alpha is not yet used\n\
std_msgs/ColorRGBA[] colors\n\
\n\
# NOTE: only used for text markers\n\
string text\n\
\n\
# NOTE: only used for MESH_RESOURCE markers\n\
string mesh_resource\n\
bool mesh_use_embedded_materials\n\
\n\
================================================================================\n\
MSG: std_msgs/Header\n\
# Standard metadata for higher-level stamped data types.\n\
# This is generally used to communicate timestamped data \n\
# in a particular coordinate frame.\n\
# \n\
# sequence ID: consecutively increasing ID \n\
uint32 seq\n\
#Two-integer timestamp that is expressed as:\n\
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')\n\
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')\n\
# time-handling sugar is provided by the client library\n\
time stamp\n\
#Frame this data is associated with\n\
# 0: no frame\n\
# 1: global frame\n\
string frame_id\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Pose\n\
# A representation of pose in free space, composed of position and orientation. \n\
Point position\n\
Quaternion orientation\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Point\n\
# This contains the position of a point in free space\n\
float64 x\n\
float64 y\n\
float64 z\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Quaternion\n\
# This represents an orientation in free space in quaternion form.\n\
\n\
float64 x\n\
float64 y\n\
float64 z\n\
float64 w\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Vector3\n\
# This represents a vector in free space. \n\
# It is only meant to represent a direction. Therefore, it does not\n\
# make sense to apply a translation to it (e.g., when applying a \n\
# generic rigid transformation to a Vector3, tf2 will only apply the\n\
# rotation). If you want your data to be translatable too, use the\n\
# geometry_msgs/Point message instead.\n\
\n\
float64 x\n\
float64 y\n\
float64 z\n\
================================================================================\n\
MSG: std_msgs/ColorRGBA\n\
float32 r\n\
float32 g\n\
float32 b\n\
float32 a\n\
\n\
================================================================================\n\
MSG: sensor_msgs/PointCloud2\n\
# This message holds a collection of N-dimensional points, which may\n\
# contain additional information such as normals, intensity, etc. The\n\
# point data is stored as a binary blob, its layout described by the\n\
# contents of the \"fields\" array.\n\
\n\
# The point cloud data may be organized 2d (image-like) or 1d\n\
# (unordered). Point clouds organized as 2d images may be produced by\n\
# camera depth sensors such as stereo or time-of-flight.\n\
\n\
# Time of sensor data acquisition, and the coordinate frame ID (for 3d\n\
# points).\n\
Header header\n\
\n\
# 2D structure of the point cloud. If the cloud is unordered, height is\n\
# 1 and width is the length of the point cloud.\n\
uint32 height\n\
uint32 width\n\
\n\
# Describes the channels and their layout in the binary data blob.\n\
PointField[] fields\n\
\n\
bool    is_bigendian # Is this data bigendian?\n\
uint32  point_step   # Length of a point in bytes\n\
uint32  row_step     # Length of a row in bytes\n\
uint8[] data         # Actual point data, size is (row_step*height)\n\
\n\
bool is_dense        # True if there are no invalid points\n\
\n\
================================================================================\n\
MSG: sensor_msgs/PointField\n\
# This message holds the description of one point entry in the\n\
# PointCloud2 message format.\n\
uint8 INT8    = 1\n\
uint8 UINT8   = 2\n\
uint8 INT16   = 3\n\
uint8 UINT16  = 4\n\
uint8 INT32   = 5\n\
uint8 UINT32  = 6\n\
uint8 FLOAT32 = 7\n\
uint8 FLOAT64 = 8\n\
\n\
string name      # Name of field\n\
uint32 offset    # Offset from start of point struct\n\
uint8  datatype  # Datatype enumeration, see above\n\
uint32 count     # How many elements in the field\n\
";
  }

  static const char* value(const ::ouster_lidar::MarkerWithCloud_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::ouster_lidar::MarkerWithCloud_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.marker);
      stream.next(m.pointcloud);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct MarkerWithCloud_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::ouster_lidar::MarkerWithCloud_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::ouster_lidar::MarkerWithCloud_<ContainerAllocator>& v)
  {
    s << indent << "marker: ";
    s << std::endl;
    Printer< ::visualization_msgs::Marker_<ContainerAllocator> >::stream(s, indent + "  ", v.marker);
    s << indent << "pointcloud: ";
    s << std::endl;
    Printer< ::sensor_msgs::PointCloud2_<ContainerAllocator> >::stream(s, indent + "  ", v.pointcloud);
  }
};

} // namespace message_operations
} // namespace ros

#endif // OUSTER_LIDAR_MESSAGE_MARKERWITHCLOUD_H
