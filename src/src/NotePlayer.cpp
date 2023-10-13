#include <Arduino.h>

#include "NotePlayer.h"
#include "InputHandler.h"
#include "Pinout.h"

#include "StatusLeds.h"
#include "NoteRecorder.h"

namespace NotePlayer
{
    void PlayNoteSync(int note, unsigned long duration = 0UL)
    {
        tone(PIN_BUZZER,note);

        if(duration != 0UL)
        {
            delay(duration);
            StopNote();
        }
    }

    void StopNote()
    {
        noTone(PIN_BUZZER);
    }

    void checkNote(int note)
    {
        if(!InputHandler::GetNoteState(note)) return;

        NoteRecorder::NoteBegin(note);

        while (InputHandler::GetNoteState(note)) PlayNoteSync(note);

        NoteRecorder::NoteEnd();

        StopNote();

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