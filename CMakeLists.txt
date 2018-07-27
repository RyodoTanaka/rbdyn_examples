cmake_minimum_required(VERSION 2.8)
project(RBDyn_example)
set(CMAKE_CXX_FLAGS "-Wall -std=c++11")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)

# For RBDyn


# For Boost
#find_package(Boost COMPONENTS system REQUIRED)

# For Eigen
INCLUDE(cmake/eigen.cmake)
SEARCH_FOR_EIGEN()

# # For Python
# include_directories("/usr/include/python2.7")

add_executable(RevRobot
  src/RevRobot.cpp
)

target_link_libraries(RevRobot
  ${Boost_FILESYSTEM_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_PROGRAM_OPTIONS_LIBRARY}
 )
