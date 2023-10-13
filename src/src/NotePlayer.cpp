#include <Arduino.h>

#include "NotePlayer.h"
#include "InputHandler.h"
#include "Pinout.h"


namespace NotePlayer
{
    void checkNote(int note)
    {
        while (InputHandler::GetNoteState(note))
        {
            tone(PIN_BUZZER, note);
        }

        noTone(PIN_BUZZER);
    }

    void NoteLoop()
    {
        checkNote(NOTE_C);
        checkNote(NOTE_D);
        checkNote(NOTE_E);
        checkNote(NOTE_F);
        checkNote(NOTE_G);
        checkNote(NOTE_A);
        checkNote(NOTE_B);
    }

}