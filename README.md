# RBDyn Examples
C++ examples to utilize RBDyn.  

### Dependencies

- [Eigen3ToPython](https://github.com/jrl-umi3218/Eigen3ToPython)
- [SpaceVecAlg](https://github.com/jrl-umi3218/SpaceVecAlg)
- [RBDyn](https://github.com/jrl-umi3218/RBDyn)
- [mc_rbdyn_urdf](https://github.com/jrl-umi3218/mc_rbdyn_urdf)

## Installation
### Install by script
````bash
$ source install.bash
``

### Install by manual
#### 0. Install dependencies
```bash
$ sudo apt-get install git cmake pkg-config doxygen g++ libboost1.58-dev libboost1.58-all-dev libeigen3-dev libyaml-cpp-dev python-pip python2.7-dev make libtinyxml2-dev libnotify-bin -y
```

#### 1. Install Eigen3ToPython
```bash
$ git clone --recursive https://github.com/jrl-umi3218/Eigen3ToPython.git
$ cd Eigen3ToPython
$ mkdir build
$ cd build
$ cmake .. -DPYTHON_BINDING_USER_INSTALL=ON
$ make -j`nproc`
$ sudo make install
```

#### 2. Install SpaceVecAlg
```bash
$ git clone --recursive https://github.com/jrl-umi3218/SpaceVecAlg.git
$ cd SpaceVecAlg
$ mkdir build
$ cd build
$ cmake .. -DPYTHON_BINDING=ON -DPYTHON_BINDING_USER_INSTALL=ON
$ make -j`nproc`
$ sudo make install
```

#### 3. Install RBDyn
```bash
$ git clone --recursive https://github.com/jrl-umi3218/RBDyn.git
$ cd RBDyn
$ mkdir build
$ cd build
$ cmake .. -DPYTHON_BINDING=ON -DPYTHON_BINDING_USER_INSTALL_DEFAULT=ON -DPYTHON_BINDING_USER_INSTALL=ON
$ make -j`nproc`
$ sudo make install
```

#### 4. Install mc_rbdyn_urdf
```bash
$ git clone --recursive https://github.com/jrl-umi3218/mc_rbdyn_urdf.git
$ cd mc_rbdyn_urdf
$ mkdir build
$ cd build
$ cmake .. -DPYTHON_BINDING=ON -DPYTHON_BINDING_USER_INSTALL=ON
$ make -j`nproc`
$ sudo make install
```

#### 5. Export environment argument
```bash
$ export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib
```

#### 6. Build RBDyn_example
```bash
$ cd rbdyn_examples
$ source compile.bash
```

#### 7. Execute examples
```bash
$ rbdynrun <TAB>
```

## Usage
#### robot_config_example.cpp
```bash
$ rbdynrun robot_config_example
```
Just load the robot description from source code.

#### urdf_fk.cpp
```bash
$ rbdynrun urdf_fk
```
Load robot description from URDF file.  
Then solve the FK and print the homogeneous matrix for each links in the world frame.

#### urdf_ik.cpp
```bash
$ rbdynrun urdf_ik
```
Load robot description from URDF file.  
Then solve the IK and print the homogeneous matrix for each links in the world frame.

#### yaml_test.cpp
```bash
$ rbdynrun yaml_test
```
Load YAML file from `yaml/test.yaml`
