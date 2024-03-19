#pragma once

#include <Arduino.h>
#include "DEV_Config.h"
#include "EPD.h"


class Display {

public:
    Display() {
        
    }
    ~Display() {
        poweroff();
    }

    void init() {
        Serial.println("Initializing Display");
        DEV_Module_Init();
        poweron();
    }

    void poweron() {
        EPD_5IN83_V2_Init();
        clearScreen();
    }

    void poweroff() {
        EPD_5IN83_V2_Sleep();
    }

    void clearScreen() {
        EPD_5IN83_V2_Clear();
    }

    void showImage(unsigned char *image){
        EPD_5IN83_V2_Display(image);
    }

};