#include <Arduino.h>

#include "Pinout.h"

#include "Music\NotePlayer.h"
#include "Music\NoteRecorder.h"

#include "Input\InputHandler.h"

#include "Music\Notes.h"

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

    void checkNote(int noteIndex)
    {
        if(!InputHandler::GetNoteState(noteIndex)) return;

        int note = Notes::getNote(noteIndex);

        NoteRecorder::NoteBegin(note);

        while (InputHandler::GetNoteState(noteIndex)) PlayNoteSync(note);

        NoteRecorder::NoteEnd();

        StopNote();

    }

    void NoteLoop()
    {
        checkNote(0);
        checkNote(1);
        checkNote(2);
        checkNote(3);
        checkNote(4);
        checkNote(5);
        checkNote(6);
    }
}