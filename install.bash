#!/bin/bash

SCRIPT_PATH=$( dirname ${BASH_SOURCE:-$0} )
CURRENT=$(pwd)

# Pre requirements
sudo apt-get install git cmake pkg-config doxygen g++ libboost1.58-dev libboost1.58-all-dev libeigen3-dev libyaml-cpp-dev python-pip python2.7-dev make libtinyxml2-dev libnotify-bin -y

cd ../
# Eigen3ToPython
git clone --recursive https://github.com/jrl-umi3218/Eigen3ToPython.git
cd Eigen3ToPython
mkdir build
cd build
cmake .. -DPYTHON_BINDING_USER_INSTALL=ON
make -j`nproc`
sudo make install
cd ../..

# SpaceVecAlg
git clone --recursive https://github.com/jrl-umi3218/SpaceVecAlg.git
cd SpaceVecAlg
mkdir build
cd build
cmake .. -DPYTHON_BINDING=ON -DPYTHON_BINDING_USER_INSTALL=ON
make -j`nproc`
sudo make install
cd ../..

# RBDyn
git clone --recursive  https://github.com/jrl-umi3218/RBDyn.git
cd RBDyn
mkdir build
cd build
cmake .. -DPYTHON_BINDING=ON -DPYTHON_BINDING_USER_INSTALL_DEFAULT=ON -DPYTHON_BINDING_USER_INSTALL=ON
make -j`nproc`
sudo make install
cd ../..

# mc_rbdyn_urdf
git clone --recursive https://github.com/jrl-umi3218/mc_rbdyn_urdf.git
cd mc_rbdyn_urdf
mkdir build
cd build
cmake .. -DPYTHON_BINDING=ON -DPYTHON_BINDING_USER_INSTALL=ON
make -j`nproc`
sudo make install
cd ../..

# Export the env
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib

# Build the rbdyn_example
cd rbdyn_examples
source compile.bash
return $?
