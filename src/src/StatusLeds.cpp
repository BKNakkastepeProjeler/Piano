#include <Arduino.h>

#include "StatusLeds.h"
#include "Pinout.h"

namespace StatusLeds
{
    void StatusLedsInit()
    {
        pinMode(LED_RECORDSTATUS, OUTPUT);
    }
    
    void SetLed(int LED, bool value)
    {
        digitalWrite(LED, value == true ? HIGH : LOW);
    }
}