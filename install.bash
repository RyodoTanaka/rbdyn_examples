#!/bin/bash

SCRIPT_PATH=$( dirname ${BASH_SOURCE:-$0} )
CURRENT=$(pwd)

# Pre requirements
sudo apt -y install git cmake pkg-config doxygen g++ libboost-dev libeigen3-dev libyaml-cpp-dev

# SpaceVecAlg
cd ../
git clone --recursive https://github.com/jrl-umi3218/SpaceVecAlg.git
cd SpaceVecAlg
mkdir build
cd build
cmake -DPYTHON_BINDING=OFF ..
make -j`nproc`
sudo make install
cd ../../

# RBDyn
git clone --recursive  https://github.com/jrl-umi3218/RBDyn.git
cd RBDyn
mkdir build
cd build
cmake -DPYTHON_BINDING=OFF ..
make -j`nproc`
sudo make install
cd ../..

# mc_rbdyn_urdf
git clone --recursive https://github.com/jrl-umi3218/mc_rbdyn_urdf.git
cd mc_rbdyn_urdf
mkdir build
cd build
cmake -DPYTHON_BINDING=OFF ..
make -j`nproc`
sudo make install
cd ../..

# Export the env
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib

# Build the rbdyn_example
cd rbdyn_examples
source compile.bash
cd ${CURRENT}
