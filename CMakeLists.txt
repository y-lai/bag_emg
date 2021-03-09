cmake_minimum_required(VERSION 3.0.2)
project(bag_emg)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  rosbag
  roscpp
  track_robot_msgs
  labjackt7test_msgs
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES bag_emg
  CATKIN_DEPENDS rosbag roscpp track_robot_msgs labjackt7test_msgs
#  DEPENDS system_lib
)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

add_executable(${PROJECT_NAME}_node
  src/bag_emg.cpp
)
target_link_libraries(${PROJECT_NAME}_node
  ${catkin_LIBRARIES}
)

