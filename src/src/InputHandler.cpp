#include <Arduino.h>

#include "NotePlayer.h"
#include "Pinout.h"

namespace InputHandler
{
    void setInput(uint8_t pin)
    {
        pinMode(pin, INPUT);
        digitalWrite(pin,HIGH);
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
    }
    
    bool GetNoteState(int note)
    {
        int PIN = -1;

        switch (note)
        {
            case NOTE_C: PIN = PIN_INP1; break;
            case NOTE_D: PIN = PIN_INP2; break;
            case NOTE_E: PIN = PIN_INP3; break;
            case NOTE_F: PIN = PIN_INP4; break;
            case NOTE_G: PIN = PIN_INP5; break;
            case NOTE_A: PIN = PIN_INP6; break;
            case NOTE_B: PIN = PIN_INP7; break;
        }

        if(PIN == -1) return false;

        return (digitalRead(PIN) == HIGH ? LOW : HIGH);
    }

}
