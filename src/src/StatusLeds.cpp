#include <Arduino.h>

#include "StatusLeds.h"
#include "Pinout.h"

namespace StatusLeds
{
    void StatusLedsInit()
    {
        pinMode(LED_RECORDSTATUS, OUTPUT);
        pinMode(LED_PLAYING, OUTPUT);
    }
    
    void SetLed(int LED, bool value)
    {
        digitalWrite(LED, value == true ? HIGH : LOW);
    }

    void BlinkLed(int LED, int count, int delayMS)
    {
        for(int i = 0; i < count; i++)
        {
            SetLed(LED, true);
            delay(delayMS);
            SetLed(LED, false);
            if(i != count - 1) delay(delayMS);
        }
    }
}