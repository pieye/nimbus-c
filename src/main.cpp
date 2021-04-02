#include <stdio.h>
#include <unistd.h>
#include "nimbusPreprocessInterface.h"

int g_cnt;

void imageCallback(void* unused0, void* img, void* unused1) {
    //Get Image Data
    //Image Data contained in a 1D array. 352*286 pixels. 
    uint16_t* ampl      = nimbus_seq_get_amplitude(img);
    uint8_t* conf       = nimbus_seq_get_confidence(img);
    uint16_t* radial    = nimbus_seq_get_radial_dist(img);
    int16_t* x          = nimbus_seq_get_x(img);
    int16_t* y          = nimbus_seq_get_y(img);
    int16_t* z          = nimbus_seq_get_z(img);
    ImgHeader_t* header = nimbus_seq_get_header(img);
    printf("got an image\n");

    //Change Exposure Settings
    AutoExposureParams_t m_params;
    m_params.amplitude     = 1000;    //0.0 - ~1500.0
    m_params.max_exposure  = 32767;   //0-32767
    m_params.hdr_factor    = 0.3;     //0.0 - 1.0
    m_params.exposure_mode = 3;       //MANUAL = 0, MANUAL_HDR  = 1, AUTO = 2, AUTO_HDR = 3
    bool set_exposure      = nimbus_autoexposure_set_params(&m_params);
    
    nimbus_seq_del(img); //<- free the image pointer this call is necessary to return img resource to nimbus
}

int main(int argc, char** argv) {
int i;

printf("nimbus-userland version: %s\n", nimbus_get_version());

if (nimbus_preproc_init()) {
    nimbus_preproc_seq_cb(imageCallback);
    g_cnt = 0;
    while (g_cnt < 100) {
        usleep(10000);
    }
}
else {
    printf("init nimbus failed!\n");
}
    return 0;
}