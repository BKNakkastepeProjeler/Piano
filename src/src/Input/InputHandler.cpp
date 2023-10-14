#include <Arduino.h>

#include "Music\NotePlayer.h"
#include "Input\InputHandler.h"
#include "Pinout.h"

namespace InputHandler
{

    void setInput(uint8_t pin)
    {
        pinMode(pin, INPUT);
        digitalWrite(pin, HIGH);
    }

    void InputHandlerInit()
    {
        setInput(PIN_INP1);
        setInput(PIN_INP2);
        setInput(PIN_INP3);
        setInput(PIN_INP4);
        setInput(PIN_INP5);
        setInput(PIN_INP6);
        setInput(PIN_INP7);
        
        setInput(BTN_RECORD);

        setInput(BTN_DECREASEOCTAVE);
        setInput(BTN_INCREASEOCTAVE);
    }

    bool GetButtonValue(int PIN)
    {
        return !digitalRead(PIN);
    }

    bool GetNoteState(int noteIndex)
    {
        switch (noteIndex)
        {
            case 0: return GetButtonValue(PIN_INP1);
            case 1: return GetButtonValue(PIN_INP2);
            case 2: return GetButtonValue(PIN_INP3);
            case 3: return GetButtonValue(PIN_INP4);
            case 4: return GetButtonValue(PIN_INP5);
            case 5: return GetButtonValue(PIN_INP6);
            case 6: return GetButtonValue(PIN_INP7);
            default: return false;
        }
    }


    ButtonState GetButtonState(int PIN)
    {
        const int HoldDuration = 1000;


        unsigned int inputDuration = 0;

        while (GetButtonValue(PIN))
        {
            inputDuration += 10;

            if(inputDuration == HoldDuration) break;

            delay(10);
        }

        if (inputDuration == 0) return None;
        if(inputDuration == 1000) return Hold;
        return Down;
    }



}