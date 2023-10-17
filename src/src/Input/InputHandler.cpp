#include <Arduino.h>

#include "Music\NotePlayer.h"
#include "Input\InputHandler.h"
#include "Pinout.h"

#include <CapacitiveSensor.h>

namespace InputHandler
{
    const int threshold = 100;
    const int samples = 10000;

    CapacitiveSensor caps[] =
        {
            CapacitiveSensor(PIN_INPCOMMON, PIN_INP1),
            CapacitiveSensor(PIN_INPCOMMON, PIN_INP2),
            CapacitiveSensor(PIN_INPCOMMON, PIN_INP3),
            CapacitiveSensor(PIN_INPCOMMON, PIN_INP4),
            CapacitiveSensor(PIN_INPCOMMON, PIN_INP5),
            CapacitiveSensor(PIN_INPCOMMON, PIN_INP6),
            CapacitiveSensor(PIN_INPCOMMON, PIN_INP7)
        };


    void setInputButton(uint8_t pin)
    {
        pinMode(pin, INPUT);
        digitalWrite(pin, HIGH);
    }

    void setCaps()
    {
        for (size_t i = 0; i < 7; i++)
        {
            caps[i].set_CS_AutocaL_Millis(0xFFFFFFFF);
        }
    }

    void DebugPrintLoop()
    {
        while (true)
        {
            String s1 = String(caps[0].capacitiveSensor(samples));
            String s2 = String(caps[1].capacitiveSensor(samples));
            String s3 = String(caps[2].capacitiveSensor(samples));
            String s4 = String(caps[3].capacitiveSensor(samples));
            String s5 = String(caps[4].capacitiveSensor(samples));
            String s6 = String(caps[5].capacitiveSensor(samples));
            String s7 = String(caps[6].capacitiveSensor(samples));

            Serial.println(s1 + " // " + s2 + " // " + s3 + " // " + s4 + " // " + s5 + " // " + s6 + " // " + s7);
        }
        
    }

    void InputHandlerInit()
    {
        setCaps();

        setInputButton(BTN_RECORD);

        setInputButton(BTN_DECREASEOCTAVE);
        setInputButton(BTN_INCREASEOCTAVE);

        //DebugPrintLoop();
    }

    bool GetButtonValue(int PIN)
    {
        return !digitalRead(PIN);
    }
    ButtonState GetButtonState(int PIN)
    {
        const int HoldDuration = 1000;

        unsigned int inputDuration = 0;

        while (GetButtonValue(PIN))
        {
            inputDuration += 10;

            if (inputDuration == HoldDuration)
                break;

            delay(10);
        }

        if (inputDuration == 0)
            return None;
        if (inputDuration == 1000)
            return Hold;
        return Down;
    }

    bool GetNoteState(int noteIndex)
    {
        if(noteIndex < 0 || noteIndex > 6) return false;

        return caps[noteIndex].capacitiveSensor(samples) > threshold;
    }


}