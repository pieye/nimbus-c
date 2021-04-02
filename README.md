# Nimbus-C

## Introduction
here you can find our prepared [Raspberry Pi OS (buster)](https://cloud.pieye.org/index.php/s/nimbus3D) images.
Fruthermore here is the official [documentation](https://nimbus-docs.readthedocs.io/en/latest/index.html).

## Adding a custom processing stage
### C-Interface
After having built and installed nimbus-userland (make install), all libraries are installed under /usr/local/lib, all headers are installed under /usr/local/include The header nimbusPreprocessInterface.h contains a low level c interface to libnimbus-preprocessing.so. This is useful when you want to integrate the nimbus 3d with external applications.

The following example (src/main.cpp) shows a basic implemenation to get the image data in C/C++;
It is important to understand, that this implementation directly integrates into the preprocessing toolchain. Therefore, it is triggered synchronous and any runtime inside the callback will reduce the overall framerate!

## Run the example

Create a build folder

``` 
mkdir build
cd build
``` 
Run Cmake
``` 
cmake ..
make all
``` 
Run the compiled program
``` 
./nimbus-c
``` 
