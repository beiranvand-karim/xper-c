# xper-cpp

## project implementation

### 1 _ download and install **_cmake_**.
You can download and install **_cmake_** from [cmake download](https://cmake.org/download/) and [cmake install](https://cmake.org/install/) .

To download and install **_cmake_** on mac from terminal, [click here](http://macappstore.org/cmake/).

### 2 _ Add requirement libraries 

## mac os

* Install **_pkgconfig_** as package manager:
> brew install pkg-config

* Download **_gtkmm_** library for mac from [gtkmm lib](http://macappstore.org/gtkmm/) or from terminal :
> brew install gtkmm3 

> pkg-config  --cflags gtkmm-3.0

or 

> pkg-config  --cflags gtkmm3
### 3 _ Build and run the project in terminal
Open xper-cpp directory then:

```
mkdir build
cd build
cmake ../src/
make 
./xper-cpp
``` 

### 4 _ Build and run the project in the **_clion_** idea
Open **_CMakeLists.txt_** and click the load **_CMakeList.txt_** button then Run the **_xper-cpp_**.
