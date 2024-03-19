#pragma once

#include "imagedata.h"

class ImageService {

private:
    unsigned char image[38880];

public:
    ImageService(){
        for(int i = 0; i < 38880; ++i) {
            image[i] = ~gImage_5in83_V2[i];
        }
    };

    void setImage(unsigned char newImage[38880]) {
        for(int i = 0; i < 38880; i++) {
            image[i] = newImage[i];
        }
    }

    unsigned char *getImagePointer() {
        return image;
    }
};