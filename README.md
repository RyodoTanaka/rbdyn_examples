# RBDyn Examples
C++ examples to utilize

- [RBDyn](https://github.com/jrl-umi3218/RBDyn.git)
- [mc_rbdyn_urdf](https://github.com/jrl-umi3218/mc_rbdyn_urdf.git)

Here is the examples

|Program file | About |
|:---:|:---|
|RevRobot.cpp| Just road the robot description from source code.|
|urdf_example.cpp| Road robot description from URDF file.|

## Installation 
#### 1. Install RBDyn
```bash
$ git clone https://github.com/jrl-umi3218/RBDyn.git
$ cd RBDyn
$ mkdir build
$ cd build
$ cmake -DPYTHON_BINDING=OFF ..
$ make -j`nproc`
$ sudo make install
```

#### 2. Install mc_rbdyn_urdf
```bash
$ git clone https://github.com/jrl-umi3218/mc_rbdyn_urdf.git
$ cd mc_rbdyn_urdf
$ mkdir build
$ cd build
$ cmake -DPYTHON_BINDING=OFF ..
$ make -j`nproc`
$ sudo make install
```

#### 3. Export environment argument
```bash
$ export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib
```

#### 4. Build RBDyn_example
```bash
$ source compile.bash
```

#### 5. Execute examples
```bash
$ rbdynrun <TAB>
```

## Usage
#### RevRobot.cpp
```bash
$ rbdynrun RevRobot
```
Just road the robot description from source code.|

#### urdf_example.cpp
```bash
$ rbdynrun urdf_example <URDF file path>
```
Road robot description from URDF file.
