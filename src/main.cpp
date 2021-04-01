#include <stdio.h>
#include <unistd.h>
#include "nimbusPreprocessInterface.h"

int g_cnt;

void imageCallback(void* unused0, void* img, void* unused1) {
    uint16_t* ampl = nimbus_seq_get_amplitude(img);
    uint8_t* conf = nimbus_seq_get_confidence(img);
    ImgHeader_t* header = nimbus_seq_get_header(img);
    printf("got an image\n");
    g_cnt++;
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