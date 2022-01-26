# xper-cpp
___
## Install dependencies

### 1 _ download and install **_qt and qmake_**.
for Ubuntu :
```
sudo apt-get update -y
sudo apt-get install -y qt5-qmake
```

for mac :
```
brew install qt
```
or
```
brew install qt5
```

### 2 _ Build and run the project in terminal
open a terminal in the project directory:

```
mkdir build
cd build
qmake ../
make 
./xper-cpp
```