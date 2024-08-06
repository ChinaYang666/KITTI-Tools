cmake_minimum_required(VERSION 3.0.2)
project(kitti_tools)

set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wall -g")




find_package(catkin REQUIRED COMPONENTS
  sensor_msgs
  roscpp
  rospy
  std_msgs
)

# find_package(Eigen3 3.3.7 REQUIRED)
find_package(PCL 1.10.0 REQUIRED)
# find_package(OpenCV 4.4.0 REQUIRED)

# find_package(Ceres 2.2.0 REQUIRED)




include_directories(
  include
	${catkin_INCLUDE_DIRS} 
	${PCL_INCLUDE_DIRS}
  ${CERES_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS})



catkin_package(
  CATKIN_DEPENDS  roscpp rospy std_msgs sensor_msgs
  DEPENDS PCL 
  INCLUDE_DIRS include
)


add_executable(kitti_toolsNode src/kitti_toolsMain.cpp src/kitti_tools.cpp)
target_link_libraries(kitti_toolsNode ${catkin_LIBRARIES} ${PCL_LIBRARIES})
