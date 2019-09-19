cmake_minimum_required(VERSION 2.8.3)
project(ouster_lidar)
add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
roscpp
std_msgs
pcl_ros
sensor_msgs	
cv_bridge
geometry_msgs
tf
visualization_msgs
message_generation
)

add_message_files(
  FILES
  MarkerWithCloud.msg
  MarkerWithCloudArray.msg
  MarkerClassification.msg
  DetectedObject.msg
  DetectedObjectArray.msg
)

find_package(OpenCV)
include_directories(${OpenCV_INCLUDE_DIRS})
generate_messages(
DEPENDENCIES
std_msgs
geometry_msgs
visualization_msgs
sensor_msgs
)

catkin_package(
CATKIN_DEPENDS  roscpp std_msgs pcl_ros sensor_msgs geometry_msgs visualization_msgs message_runtime
DEPENDS system_lib 
)


include_directories(include)
include_directories(
${catkin_INCLUDE_DIRS}
${PCL_INCLUDE_DIRS}
${OpenCV_INCLUDE_DIRS}
${OpenCV_LIB_COMPONENTS}
${OpenCV_LIBRARIES}
)


add_library(HungarianAlg src/HungarianAlg.cpp)

add_executable(tracking src/tracking.cpp)
target_link_libraries(tracking ${catkin_LIBRARIES} ${OpenCV_LIBS})
target_link_libraries(tracking HungarianAlg)

add_executable(separate_ground src/separate_ground.cpp)
target_link_libraries(separate_ground ${catkin_LIBRARIES} ${OpenCV_LIBS})


add_executable(segmentation src/segmentation.cpp)
target_link_libraries(segmentation ${catkin_LIBRARIES} ${OpenCV_LIBS})
# add_dependencies(segmentation src/segmentation.cpp) 18.04

add_executable(classification src/classification.cpp)
target_link_libraries(classification ${catkin_LIBRARIES} ${OpenCV_LIBS})
# add_dependencies(classification src/classification.cpp) only 18.04


add_executable(l_shape src/lidar_naive_l_shape_detect.cpp)
target_link_libraries(l_shape ${catkin_LIBRARIES} ${OpenCV_LIBS})
# add_dependencies(l_shape src/lidar_naive_l_shape_detect.cpp)



link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})