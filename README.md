# RBDyn Examples
C++ examples to utilize

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
$ sudo apt install git cmake pkg-config doxygen g++ libboost-dev libeigen3-dev libyaml-cpp-dev
```

#### 1. Install SpaceVecAlg
```bash
$ git clone --recursive https://github.com/jrl-umi3218/SpaceVecAlg.git
$ cd SpaceVecAlg
$ mkdir build
$ cd build
$ cmake -DPYTHON_BINDING=OFF ..
$ make -j`nproc`
$ sudo make install
```

#### 2. Install RBDyn
```bash
$ git clone --recursive https://github.com/jrl-umi3218/RBDyn.git
$ cd RBDyn
$ mkdir build
$ cd build
$ cmake -DPYTHON_BINDING=OFF ..
$ make -j`nproc`
$ sudo make install
```

#### 3. Install mc_rbdyn_urdf
```bash
$ git clone --recursive https://github.com/jrl-umi3218/mc_rbdyn_urdf.git
$ cd mc_rbdyn_urdf
$ mkdir build
$ cd build
$ cmake -DPYTHON_BINDING=OFF ..
$ make -j`nproc`
$ sudo make install
```

#### 4. Export environment argument
```bash
$ export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib
```

#### 5. Build RBDyn_example
```bash
$ cd rbdyn_examples
$ source compile.bash
```

#### 6. Execute examples
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
