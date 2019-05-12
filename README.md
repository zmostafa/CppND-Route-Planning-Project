# Route Planning Project Starter Code  [![Build Status](https://travis-ci.com/zmostafa/CppND-Route-Planning-Project.svg?branch=master)](https://travis-ci.com/zmostafa/CppND-Route-Planning-Project)

This is the starter code for the Route Planning project. Instructions for each exercise can be found in the `instructions` directory, and unit tests for some exercises in the `test` directory.

## Cloning

When cloning this project, be sure to use the `--recurse-submodules` flag. Using HTTPS:
```
git clone https://github.com/udacity/CppND-Route-Planning-Project.git --recurse-submodules
```
or with SSH:
```
git clone git@github.com:udacity/CppND-Route-Planning-Project.git --recurse-submodules
```

## Compiling and Running

### Compiling
To compile the project, first, create a `build` directory and change to that directory:
```
mkdir build && cd build
```
From within the `build` directory, then run `cmake` and `make` as follows:
```
cmake ..
make
```
### Running
The executables will be placed in the `bin` directory. From within `build`, you can run the project as follows:
```
../bin/<name-of-parent-directory> -f ../map.osm
```

## Testing

For exercises that have unit tests, the project must be built with the approprate test cpp file. This can be done by passing a string with the `-DTESTING` flag in `cmake`. For example, from the build directory:
```
cmake -DTESTING="EnableTesting" ..
make
```
Those commands will build the code with the tests for all exercisse. The tests can then be run from the `build` directory as follows:
```
../bin/<test_name>
```

| Exercise Name               |       Test Name          |
|-----------------------------|:------------------------:|
| Fill Out Route Model        |       "RouteModel"       |
| Fill Out Node Class         |       "RMNodeClass"      |
| Create RouteModel Nodes     |        "RMSNodes"        |
| Write the Distance Function |        "NodeDist"        |
| Create Road to Node Hashmap |       "NodeToRoad"       |
| Write FindNeighbors         |      "FindNeighbors"     |
| Find the Closest Node       |       "FindClosest"      |
| Write the A\* Search Stub   |        "AStarStub"       |
| Finish A\* Search           |       "AStarSearch"      |

# Ubuntu 16.04 installation
The Virtual Desktop from Udacity's workspace is using Ubuntu 18.03, with g++-7 and newer cmake version.

## Install package and libs dependancies
Install packages from the normal distribution:
```
$ sudo apt update
$ sudo apt install build-essential
$ sudo apt install libcairo2-dev
$ sudo apt install libgraphicsmagick1-dev
$ sudo apt install libpng-dev
```

## Install recent GCC

```
$ sudo add-apt-repository ppa:ubuntu-toolchain-r/test -y
$ sudo apt-get update
$ sudo apt-get install g++-7
```

Then you need to link the g++-7 to your g++ command, then test version:
```
$ sudo rm /usr/bin/g++
$ sudo ln -s /usr/bin/g++-7 /usr/bin/g++
$ g++ --version
g++ (Ubuntu 7.4.0-1ubuntu1~16.04~ppa1) 7.4.0
```

## Compile recent Cmake
Downlaod V3.14 from (https://cmake.org/download/)

```
$ sudo apt-get purge cmake
$ tar -xzvf cmake-3.14.3.tar.gz
$ cd cmake-3.14.3
$ ./bootstrap
$ make
$ sudo make install 
```

## Compile io2d
Then compile and install io2d:
```
$ git clone --recurse-submodules https://github.com/cpp-io2d/P0267_RefImpl
$ cd P0267_RefImpl
$ mkdir Debug
$ cd Debug
$ cmake --config Debug "-DCMAKE_BUILD_TYPE=Debug" ..
$ cmake --build .
$ make
$ sudo make install
```