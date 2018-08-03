#!/bin/bash

SCRIPT_PATH=$( dirname ${BASH_SOURCE:-$0} )
CURRENT=$(pwd)

sudo apt install libeigen3-dev

cd ${SCRIPT_PATH}/..
git clone https://github.com/jrl-umi3218/RBDyn.git
cd RBDyn
mkdir build
cd build
cmake -DPYTHON_BINDING=OFF ..
make -j`nproc`
sudo make install
cd ../..

git clone https://github.com/jrl-umi3218/mc_rbdyn_urdf.git
cd mc_ubdyn_urdf
mkdir build
cd build
cmake -DPYTHON_BINDING=OFF ..
make -j`nproc`
sudo make install
cd ../..

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib

cd RBDyn_example
source compile.bash
