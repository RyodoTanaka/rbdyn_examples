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

set(SOURCE_CODE
  robot_config_example
  yaml_test
  urdf_fk
  urdf_ik
  urdf_jacobian
)

foreach(src ${SOURCE_CODE})
  add_executable(${src} src/${src}.cpp)
  target_link_libraries(${src}
    yaml-cpp
    RBDyn
    mc_rbdyn_urdf
   )
endforeach(src)
