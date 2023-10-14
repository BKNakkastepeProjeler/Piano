#pragma once

namespace StatusLeds
{
void BlinkLed(int LED, int count, int delayMS);
void StatusLedsInit();
void SetLed(int LED, bool value);
}
