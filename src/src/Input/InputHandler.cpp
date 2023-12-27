#include <Arduino.h>

#include "Music\NotePlayer.h"
#include "Input\InputHandler.h"
#include "Pinout.h"

#include <CapacitiveSensor.h>
#include "Music\Notes.h"
namespace InputHandler
{
    const int threshold = 100;
    const int samples = 10000;

    const int notePins[] =
    {
        PIN_BTNINP1,
        PIN_BTNINP2,
        PIN_BTNINP3,
        PIN_BTNINP4,
        PIN_BTNINP5,
        PIN_BTNINP6,
        PIN_BTNINP7,
        PIN_BTNINP8,
        PIN_BTNINP9,
        PIN_BTNINP10,
        PIN_BTNINP11,
        PIN_BTNINP12
    };

    void setInputButton(uint8_t pin)
    {
        pinMode(pin, INPUT);
        digitalWrite(pin, HIGH);
    }

    void InputHandlerInit()
    {

        setInputButton(BTN_RECORD);

        setInputButton(BTN_DECREASEOCTAVE);
        setInputButton(BTN_INCREASEOCTAVE);

        for(int i = 0; i < sizeof(notePins) / sizeof(int); i++)
        {
            setInputButton(notePins[i]);
        }
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
        if(noteIndex < Notes::minNoteIndex || noteIndex > Notes::maxNoteIndex) return false;

        return GetButtonValue(noteIndex);
    }


}