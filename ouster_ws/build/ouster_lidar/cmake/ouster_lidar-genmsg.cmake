# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "ouster_lidar: 5 messages, 0 services")

set(MSG_I_FLAGS "-Iouster_lidar:/home/bae/ouster_ws/src/ouster_lidar/msg;-Istd_msgs:/opt/ros/kinetic/share/std_msgs/cmake/../msg;-Igeometry_msgs:/opt/ros/kinetic/share/geometry_msgs/cmake/../msg;-Ivisualization_msgs:/opt/ros/kinetic/share/visualization_msgs/cmake/../msg;-Isensor_msgs:/opt/ros/kinetic/share/sensor_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(ouster_lidar_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/bae/ouster_ws/src/ouster_lidar/msg/DetectedObject.msg" NAME_WE)
add_custom_target(_ouster_lidar_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "ouster_lidar" "/home/bae/ouster_ws/src/ouster_lidar/msg/DetectedObject.msg" "std_msgs/ColorRGBA:geometry_msgs/Twist:std_msgs/Header:geometry_msgs/Quaternion:geometry_msgs/Point32:geometry_msgs/Vector3:geometry_msgs/Point:geometry_msgs/PolygonStamped:sensor_msgs/Image:geometry_msgs/Polygon:sensor_msgs/PointField:geometry_msgs/Pose:sensor_msgs/PointCloud2"
)

get_filename_component(_filename "/home/bae/ouster_ws/src/ouster_lidar/msg/MarkerWithCloudArray.msg" NAME_WE)
add_custom_target(_ouster_lidar_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "ouster_lidar" "/home/bae/ouster_ws/src/ouster_lidar/msg/MarkerWithCloudArray.msg" "std_msgs/ColorRGBA:geometry_msgs/Pose:std_msgs/Header:geometry_msgs/Quaternion:geometry_msgs/Point:geometry_msgs/Vector3:ouster_lidar/MarkerWithCloud:sensor_msgs/PointField:visualization_msgs/Marker:sensor_msgs/PointCloud2"
)

get_filename_component(_filename "/home/bae/ouster_ws/src/ouster_lidar/msg/MarkerWithCloud.msg" NAME_WE)
add_custom_target(_ouster_lidar_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "ouster_lidar" "/home/bae/ouster_ws/src/ouster_lidar/msg/MarkerWithCloud.msg" "std_msgs/ColorRGBA:geometry_msgs/Pose:std_msgs/Header:geometry_msgs/Quaternion:geometry_msgs/Vector3:geometry_msgs/Point:sensor_msgs/PointField:visualization_msgs/Marker:sensor_msgs/PointCloud2"
)

get_filename_component(_filename "/home/bae/ouster_ws/src/ouster_lidar/msg/DetectedObjectArray.msg" NAME_WE)
add_custom_target(_ouster_lidar_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "ouster_lidar" "/home/bae/ouster_ws/src/ouster_lidar/msg/DetectedObjectArray.msg" "std_msgs/ColorRGBA:geometry_msgs/Twist:std_msgs/Header:geometry_msgs/Quaternion:geometry_msgs/Point32:geometry_msgs/Point:geometry_msgs/Vector3:geometry_msgs/PolygonStamped:sensor_msgs/Image:geometry_msgs/Polygon:sensor_msgs/PointField:ouster_lidar/DetectedObject:geometry_msgs/Pose:sensor_msgs/PointCloud2"
)

get_filename_component(_filename "/home/bae/ouster_ws/src/ouster_lidar/msg/MarkerClassification.msg" NAME_WE)
add_custom_target(_ouster_lidar_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "ouster_lidar" "/home/bae/ouster_ws/src/ouster_lidar/msg/MarkerClassification.msg" "std_msgs/ColorRGBA:geometry_msgs/Pose:std_msgs/Header:geometry_msgs/Quaternion:geometry_msgs/Vector3:geometry_msgs/Point:visualization_msgs/MarkerArray:visualization_msgs/Marker"
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(ouster_lidar
  "/home/bae/ouster_ws/src/ouster_lidar/msg/DetectedObject.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/ColorRGBA.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Twist.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Point32.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/PolygonStamped.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/Image.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Polygon.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/PointField.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/PointCloud2.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/ouster_lidar
)
_generate_msg_cpp(ouster_lidar
  "/home/bae/ouster_ws/src/ouster_lidar/msg/MarkerWithCloudArray.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/ColorRGBA.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Vector3.msg;/home/bae/ouster_ws/src/ouster_lidar/msg/MarkerWithCloud.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/PointField.msg;/opt/ros/kinetic/share/visualization_msgs/cmake/../msg/Marker.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/PointCloud2.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/ouster_lidar
)
_generate_msg_cpp(ouster_lidar
  "/home/bae/ouster_ws/src/ouster_lidar/msg/MarkerWithCloud.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/ColorRGBA.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/PointField.msg;/opt/ros/kinetic/share/visualization_msgs/cmake/../msg/Marker.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/PointCloud2.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/ouster_lidar
)
_generate_msg_cpp(ouster_lidar
  "/home/bae/ouster_ws/src/ouster_lidar/msg/DetectedObjectArray.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/ColorRGBA.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Twist.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Point32.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/PolygonStamped.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/Image.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Polygon.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/PointField.msg;/home/bae/ouster_ws/src/ouster_lidar/msg/DetectedObject.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/PointCloud2.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/ouster_lidar
)
_generate_msg_cpp(ouster_lidar
  "/home/bae/ouster_ws/src/ouster_lidar/msg/MarkerClassification.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/ColorRGBA.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/kinetic/share/visualization_msgs/cmake/../msg/MarkerArray.msg;/opt/ros/kinetic/share/visualization_msgs/cmake/../msg/Marker.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/ouster_lidar
)

### Generating Services

### Generating Module File
_generate_module_cpp(ouster_lidar
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/ouster_lidar
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(ouster_lidar_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(ouster_lidar_generate_messages ouster_lidar_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/bae/ouster_ws/src/ouster_lidar/msg/DetectedObject.msg" NAME_WE)
add_dependencies(ouster_lidar_generate_messages_cpp _ouster_lidar_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/bae/ouster_ws/src/ouster_lidar/msg/MarkerWithCloudArray.msg" NAME_WE)
add_dependencies(ouster_lidar_generate_messages_cpp _ouster_lidar_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/bae/ouster_ws/src/ouster_lidar/msg/MarkerWithCloud.msg" NAME_WE)
add_dependencies(ouster_lidar_generate_messages_cpp _ouster_lidar_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/bae/ouster_ws/src/ouster_lidar/msg/DetectedObjectArray.msg" NAME_WE)
add_dependencies(ouster_lidar_generate_messages_cpp _ouster_lidar_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/bae/ouster_ws/src/ouster_lidar/msg/MarkerClassification.msg" NAME_WE)
add_dependencies(ouster_lidar_generate_messages_cpp _ouster_lidar_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(ouster_lidar_gencpp)
add_dependencies(ouster_lidar_gencpp ouster_lidar_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS ouster_lidar_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(ouster_lidar
  "/home/bae/ouster_ws/src/ouster_lidar/msg/DetectedObject.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/ColorRGBA.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Twist.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Point32.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/PolygonStamped.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/Image.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Polygon.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/PointField.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/PointCloud2.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/ouster_lidar
)
_generate_msg_eus(ouster_lidar
  "/home/bae/ouster_ws/src/ouster_lidar/msg/MarkerWithCloudArray.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/ColorRGBA.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Vector3.msg;/home/bae/ouster_ws/src/ouster_lidar/msg/MarkerWithCloud.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/PointField.msg;/opt/ros/kinetic/share/visualization_msgs/cmake/../msg/Marker.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/PointCloud2.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/ouster_lidar
)
_generate_msg_eus(ouster_lidar
  "/home/bae/ouster_ws/src/ouster_lidar/msg/MarkerWithCloud.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/ColorRGBA.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/PointField.msg;/opt/ros/kinetic/share/visualization_msgs/cmake/../msg/Marker.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/PointCloud2.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/ouster_lidar
)
_generate_msg_eus(ouster_lidar
  "/home/bae/ouster_ws/src/ouster_lidar/msg/DetectedObjectArray.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/ColorRGBA.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Twist.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Point32.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/PolygonStamped.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/Image.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Polygon.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/PointField.msg;/home/bae/ouster_ws/src/ouster_lidar/msg/DetectedObject.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/PointCloud2.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/ouster_lidar
)
_generate_msg_eus(ouster_lidar
  "/home/bae/ouster_ws/src/ouster_lidar/msg/MarkerClassification.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/ColorRGBA.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/kinetic/share/visualization_msgs/cmake/../msg/MarkerArray.msg;/opt/ros/kinetic/share/visualization_msgs/cmake/../msg/Marker.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/ouster_lidar
)

### Generating Services

### Generating Module File
_generate_module_eus(ouster_lidar
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/ouster_lidar
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(ouster_lidar_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(ouster_lidar_generate_messages ouster_lidar_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/bae/ouster_ws/src/ouster_lidar/msg/DetectedObject.msg" NAME_WE)
add_dependencies(ouster_lidar_generate_messages_eus _ouster_lidar_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/bae/ouster_ws/src/ouster_lidar/msg/MarkerWithCloudArray.msg" NAME_WE)
add_dependencies(ouster_lidar_generate_messages_eus _ouster_lidar_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/bae/ouster_ws/src/ouster_lidar/msg/MarkerWithCloud.msg" NAME_WE)
add_dependencies(ouster_lidar_generate_messages_eus _ouster_lidar_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/bae/ouster_ws/src/ouster_lidar/msg/DetectedObjectArray.msg" NAME_WE)
add_dependencies(ouster_lidar_generate_messages_eus _ouster_lidar_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/bae/ouster_ws/src/ouster_lidar/msg/MarkerClassification.msg" NAME_WE)
add_dependencies(ouster_lidar_generate_messages_eus _ouster_lidar_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(ouster_lidar_geneus)
add_dependencies(ouster_lidar_geneus ouster_lidar_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS ouster_lidar_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(ouster_lidar
  "/home/bae/ouster_ws/src/ouster_lidar/msg/DetectedObject.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/ColorRGBA.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Twist.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Point32.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/PolygonStamped.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/Image.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Polygon.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/PointField.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/PointCloud2.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/ouster_lidar
)
_generate_msg_lisp(ouster_lidar
  "/home/bae/ouster_ws/src/ouster_lidar/msg/MarkerWithCloudArray.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/ColorRGBA.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Vector3.msg;/home/bae/ouster_ws/src/ouster_lidar/msg/MarkerWithCloud.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/PointField.msg;/opt/ros/kinetic/share/visualization_msgs/cmake/../msg/Marker.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/PointCloud2.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/ouster_lidar
)
_generate_msg_lisp(ouster_lidar
  "/home/bae/ouster_ws/src/ouster_lidar/msg/MarkerWithCloud.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/ColorRGBA.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/PointField.msg;/opt/ros/kinetic/share/visualization_msgs/cmake/../msg/Marker.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/PointCloud2.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/ouster_lidar
)
_generate_msg_lisp(ouster_lidar
  "/home/bae/ouster_ws/src/ouster_lidar/msg/DetectedObjectArray.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/ColorRGBA.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Twist.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Point32.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/PolygonStamped.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/Image.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Polygon.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/PointField.msg;/home/bae/ouster_ws/src/ouster_lidar/msg/DetectedObject.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/PointCloud2.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/ouster_lidar
)
_generate_msg_lisp(ouster_lidar
  "/home/bae/ouster_ws/src/ouster_lidar/msg/MarkerClassification.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/ColorRGBA.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/kinetic/share/visualization_msgs/cmake/../msg/MarkerArray.msg;/opt/ros/kinetic/share/visualization_msgs/cmake/../msg/Marker.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/ouster_lidar
)

### Generating Services

### Generating Module File
_generate_module_lisp(ouster_lidar
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/ouster_lidar
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(ouster_lidar_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(ouster_lidar_generate_messages ouster_lidar_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/bae/ouster_ws/src/ouster_lidar/msg/DetectedObject.msg" NAME_WE)
add_dependencies(ouster_lidar_generate_messages_lisp _ouster_lidar_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/bae/ouster_ws/src/ouster_lidar/msg/MarkerWithCloudArray.msg" NAME_WE)
add_dependencies(ouster_lidar_generate_messages_lisp _ouster_lidar_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/bae/ouster_ws/src/ouster_lidar/msg/MarkerWithCloud.msg" NAME_WE)
add_dependencies(ouster_lidar_generate_messages_lisp _ouster_lidar_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/bae/ouster_ws/src/ouster_lidar/msg/DetectedObjectArray.msg" NAME_WE)
add_dependencies(ouster_lidar_generate_messages_lisp _ouster_lidar_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/bae/ouster_ws/src/ouster_lidar/msg/MarkerClassification.msg" NAME_WE)
add_dependencies(ouster_lidar_generate_messages_lisp _ouster_lidar_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(ouster_lidar_genlisp)
add_dependencies(ouster_lidar_genlisp ouster_lidar_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS ouster_lidar_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(ouster_lidar
  "/home/bae/ouster_ws/src/ouster_lidar/msg/DetectedObject.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/ColorRGBA.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Twist.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Point32.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/PolygonStamped.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/Image.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Polygon.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/PointField.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/PointCloud2.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/ouster_lidar
)
_generate_msg_nodejs(ouster_lidar
  "/home/bae/ouster_ws/src/ouster_lidar/msg/MarkerWithCloudArray.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/ColorRGBA.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Vector3.msg;/home/bae/ouster_ws/src/ouster_lidar/msg/MarkerWithCloud.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/PointField.msg;/opt/ros/kinetic/share/visualization_msgs/cmake/../msg/Marker.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/PointCloud2.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/ouster_lidar
)
_generate_msg_nodejs(ouster_lidar
  "/home/bae/ouster_ws/src/ouster_lidar/msg/MarkerWithCloud.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/ColorRGBA.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/PointField.msg;/opt/ros/kinetic/share/visualization_msgs/cmake/../msg/Marker.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/PointCloud2.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/ouster_lidar
)
_generate_msg_nodejs(ouster_lidar
  "/home/bae/ouster_ws/src/ouster_lidar/msg/DetectedObjectArray.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/ColorRGBA.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Twist.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Point32.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/PolygonStamped.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/Image.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Polygon.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/PointField.msg;/home/bae/ouster_ws/src/ouster_lidar/msg/DetectedObject.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/PointCloud2.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/ouster_lidar
)
_generate_msg_nodejs(ouster_lidar
  "/home/bae/ouster_ws/src/ouster_lidar/msg/MarkerClassification.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/ColorRGBA.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/kinetic/share/visualization_msgs/cmake/../msg/MarkerArray.msg;/opt/ros/kinetic/share/visualization_msgs/cmake/../msg/Marker.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/ouster_lidar
)

### Generating Services

### Generating Module File
_generate_module_nodejs(ouster_lidar
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/ouster_lidar
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(ouster_lidar_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(ouster_lidar_generate_messages ouster_lidar_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/bae/ouster_ws/src/ouster_lidar/msg/DetectedObject.msg" NAME_WE)
add_dependencies(ouster_lidar_generate_messages_nodejs _ouster_lidar_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/bae/ouster_ws/src/ouster_lidar/msg/MarkerWithCloudArray.msg" NAME_WE)
add_dependencies(ouster_lidar_generate_messages_nodejs _ouster_lidar_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/bae/ouster_ws/src/ouster_lidar/msg/MarkerWithCloud.msg" NAME_WE)
add_dependencies(ouster_lidar_generate_messages_nodejs _ouster_lidar_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/bae/ouster_ws/src/ouster_lidar/msg/DetectedObjectArray.msg" NAME_WE)
add_dependencies(ouster_lidar_generate_messages_nodejs _ouster_lidar_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/bae/ouster_ws/src/ouster_lidar/msg/MarkerClassification.msg" NAME_WE)
add_dependencies(ouster_lidar_generate_messages_nodejs _ouster_lidar_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(ouster_lidar_gennodejs)
add_dependencies(ouster_lidar_gennodejs ouster_lidar_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS ouster_lidar_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(ouster_lidar
  "/home/bae/ouster_ws/src/ouster_lidar/msg/DetectedObject.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/ColorRGBA.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Twist.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Point32.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/PolygonStamped.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/Image.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Polygon.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/PointField.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/PointCloud2.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/ouster_lidar
)
_generate_msg_py(ouster_lidar
  "/home/bae/ouster_ws/src/ouster_lidar/msg/MarkerWithCloudArray.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/ColorRGBA.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Vector3.msg;/home/bae/ouster_ws/src/ouster_lidar/msg/MarkerWithCloud.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/PointField.msg;/opt/ros/kinetic/share/visualization_msgs/cmake/../msg/Marker.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/PointCloud2.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/ouster_lidar
)
_generate_msg_py(ouster_lidar
  "/home/bae/ouster_ws/src/ouster_lidar/msg/MarkerWithCloud.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/ColorRGBA.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/PointField.msg;/opt/ros/kinetic/share/visualization_msgs/cmake/../msg/Marker.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/PointCloud2.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/ouster_lidar
)
_generate_msg_py(ouster_lidar
  "/home/bae/ouster_ws/src/ouster_lidar/msg/DetectedObjectArray.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/ColorRGBA.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Twist.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Point32.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/PolygonStamped.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/Image.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Polygon.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/PointField.msg;/home/bae/ouster_ws/src/ouster_lidar/msg/DetectedObject.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/PointCloud2.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/ouster_lidar
)
_generate_msg_py(ouster_lidar
  "/home/bae/ouster_ws/src/ouster_lidar/msg/MarkerClassification.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/ColorRGBA.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/kinetic/share/visualization_msgs/cmake/../msg/MarkerArray.msg;/opt/ros/kinetic/share/visualization_msgs/cmake/../msg/Marker.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/ouster_lidar
)

### Generating Services

### Generating Module File
_generate_module_py(ouster_lidar
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/ouster_lidar
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(ouster_lidar_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(ouster_lidar_generate_messages ouster_lidar_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/bae/ouster_ws/src/ouster_lidar/msg/DetectedObject.msg" NAME_WE)
add_dependencies(ouster_lidar_generate_messages_py _ouster_lidar_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/bae/ouster_ws/src/ouster_lidar/msg/MarkerWithCloudArray.msg" NAME_WE)
add_dependencies(ouster_lidar_generate_messages_py _ouster_lidar_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/bae/ouster_ws/src/ouster_lidar/msg/MarkerWithCloud.msg" NAME_WE)
add_dependencies(ouster_lidar_generate_messages_py _ouster_lidar_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/bae/ouster_ws/src/ouster_lidar/msg/DetectedObjectArray.msg" NAME_WE)
add_dependencies(ouster_lidar_generate_messages_py _ouster_lidar_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/bae/ouster_ws/src/ouster_lidar/msg/MarkerClassification.msg" NAME_WE)
add_dependencies(ouster_lidar_generate_messages_py _ouster_lidar_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(ouster_lidar_genpy)
add_dependencies(ouster_lidar_genpy ouster_lidar_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS ouster_lidar_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/ouster_lidar)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/ouster_lidar
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(ouster_lidar_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()
if(TARGET geometry_msgs_generate_messages_cpp)
  add_dependencies(ouster_lidar_generate_messages_cpp geometry_msgs_generate_messages_cpp)
endif()
if(TARGET visualization_msgs_generate_messages_cpp)
  add_dependencies(ouster_lidar_generate_messages_cpp visualization_msgs_generate_messages_cpp)
endif()
if(TARGET sensor_msgs_generate_messages_cpp)
  add_dependencies(ouster_lidar_generate_messages_cpp sensor_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/ouster_lidar)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/ouster_lidar
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(ouster_lidar_generate_messages_eus std_msgs_generate_messages_eus)
endif()
if(TARGET geometry_msgs_generate_messages_eus)
  add_dependencies(ouster_lidar_generate_messages_eus geometry_msgs_generate_messages_eus)
endif()
if(TARGET visualization_msgs_generate_messages_eus)
  add_dependencies(ouster_lidar_generate_messages_eus visualization_msgs_generate_messages_eus)
endif()
if(TARGET sensor_msgs_generate_messages_eus)
  add_dependencies(ouster_lidar_generate_messages_eus sensor_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/ouster_lidar)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/ouster_lidar
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(ouster_lidar_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()
if(TARGET geometry_msgs_generate_messages_lisp)
  add_dependencies(ouster_lidar_generate_messages_lisp geometry_msgs_generate_messages_lisp)
endif()
if(TARGET visualization_msgs_generate_messages_lisp)
  add_dependencies(ouster_lidar_generate_messages_lisp visualization_msgs_generate_messages_lisp)
endif()
if(TARGET sensor_msgs_generate_messages_lisp)
  add_dependencies(ouster_lidar_generate_messages_lisp sensor_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/ouster_lidar)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/ouster_lidar
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(ouster_lidar_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()
if(TARGET geometry_msgs_generate_messages_nodejs)
  add_dependencies(ouster_lidar_generate_messages_nodejs geometry_msgs_generate_messages_nodejs)
endif()
if(TARGET visualization_msgs_generate_messages_nodejs)
  add_dependencies(ouster_lidar_generate_messages_nodejs visualization_msgs_generate_messages_nodejs)
endif()
if(TARGET sensor_msgs_generate_messages_nodejs)
  add_dependencies(ouster_lidar_generate_messages_nodejs sensor_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/ouster_lidar)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/ouster_lidar\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/ouster_lidar
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(ouster_lidar_generate_messages_py std_msgs_generate_messages_py)
endif()
if(TARGET geometry_msgs_generate_messages_py)
  add_dependencies(ouster_lidar_generate_messages_py geometry_msgs_generate_messages_py)
endif()
if(TARGET visualization_msgs_generate_messages_py)
  add_dependencies(ouster_lidar_generate_messages_py visualization_msgs_generate_messages_py)
endif()
if(TARGET sensor_msgs_generate_messages_py)
  add_dependencies(ouster_lidar_generate_messages_py sensor_msgs_generate_messages_py)
endif()
