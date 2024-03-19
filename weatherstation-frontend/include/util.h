#pragma once

#include <Arduino.h>
#include "imagedata.h"

void fillWithFallback(unsigned char buffer[38880]) {
    memcpy(buffer, gImage_5in83_V2, 38880);
}
