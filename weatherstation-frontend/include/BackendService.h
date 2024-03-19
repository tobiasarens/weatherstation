#pragma once

#include <string>
#include <WiFi.h>
#include <Arduino.h>
#include <HTTPClient.h>

#include "Config.h"
#include "util.h"

class BackendService {
private:

public: 
    BackendService() {}

    void getImage(unsigned char *buffer) {
        String base_url(backend::hostname + ":" + backend::port);
        String url = base_url + "/image_c";
        Serial.println("Sending http request to: " + url);

        HTTPClient http;
        http.begin(url.c_str());

        int code = http.GET();
        if (code >0) {
            Serial.print("Response Code: ");
            Serial.println(code);

            Serial.println("content lengtht: " + String(http.getSize()));

            auto bs = http.getStream();

            int count = 0;

            while(bs.available()) {
                if (count < 38880){
                    bs.readBytes(&buffer[count], sizeof(char));
                    count++;
                } else {
                    // burn character to finish loop
                    bs.read();
                }
            }
        } else {
            Serial.print("Error: ");
            Serial.println(code);
        }

        http.end();
    }

};