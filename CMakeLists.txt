cmake_minimum_required(VERSION 2.8)
project(RBDyn_example)
set(CMAKE_CXX_FLAGS "-Wall -std=c++11")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)

# For Eigen
find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})

add_executable(robot_config_example
  src/robot_config_example.cpp
)
target_link_libraries(robot_config_example
  RBDyn
)

add_executable(urdf_fk
  src/urdf_fk.cpp
)
target_link_libraries(urdf_fk
  RBDyn
  mc_rbdyn_urdf
)
