#pragma once

#include <Arduino.h>

namespace LCD
{
    void LCDInit();
    void displayOctave();
    void displayRecordState(uint8_t state);
}