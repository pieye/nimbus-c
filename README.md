# Nimbus-C

## Introduction
Here you can find our prepared [Raspberry Pi OS (buster)](https://cloud.pieye.org/index.php/s/nimbus3D) images.
Furthermore here is the official [documentation](https://nimbus-docs.readthedocs.io/en/latest/index.html).

## Adding a custom processing stage
### C-Interface
After having built and installed nimbus-userland (make install), all libraries are installed under /usr/local/lib, all headers are installed under /usr/local/include The header nimbusPreprocessInterface.h contains a low level c interface to libnimbus-preprocessing.so. This is useful when you want to integrate the nimbus 3d with external applications.

The following example (src/main.cpp) shows a basic implemenation to get the image data in C/C++;
It is important to understand, that this implementation directly integrates into the preprocessing toolchain. Therefore, it is triggered synchronous and any runtime inside the callback will reduce the overall framerate!

## Get the image data
The following Interface is being used to access the image and point cloud data.
The image data is contained in a 1D array. 352*286 pixels.  
```c
uint16_t* ampl      = nimbus_seq_get_amplitude(img);   //Amplitude/Intensity of the pixels
uint8_t* conf       = nimbus_seq_get_confidence(img);  //Confidence Matrix showing the exposure state
uint16_t* radial    = nimbus_seq_get_radial_dist(img); //Radial Distance of the Measurement
int16_t* x          = nimbus_seq_get_x(img);           //X Position of all pixels
int16_t* y          = nimbus_seq_get_y(img);           //Y Position of all pixels
int16_t* z          = nimbus_seq_get_z(img);           //Z Position of all pixels
ImgHeader_t* header = nimbus_seq_get_header(img);
``` 

## Exposure
It is also possible to change the exposure setting inside your c/c++ application
Use the following API for this. 
```c
AutoExposureParams_t m_params;
m_params.amplitude     = amplitude;     //0.0 - ~1500.0  <-- desired amplitude for auto exposure
m_params.max_exposure  = max_exposure;  //0-32767  <-- exposure limit for auto, also functions as exposure value for manual exposure 
m_params.hdr_factor    = hdr_factor;    //0.0 - 1.0   <-- dertermines the dynamic range
m_params.exposure_mode = exposure_mode; //MANUAL = 0, MANUAL_HDR  = 1, AUTO = 2, AUTO_HDR = 3
bool set_exposure = nimbus_autoexposure_set_params(&m_params);
``` 

## Run the example

1.) Create a build folder

``` 
mkdir build
cd build
``` 

2.) Run Cmake
``` 
cmake ..
make all
``` 
3.) Run the compiled program
``` 
./nimbus-c
``` 
