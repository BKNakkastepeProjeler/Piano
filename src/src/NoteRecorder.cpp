#include <Arduino.h>

#include "StatusLeds.h"
#include "Pinout.h"
#include "NotePlayer.h"

namespace NoteRecorder
{
    bool IsRecording = false;

    unsigned long RecordingStartMilis = 0;

    const int MaxNoteCount = 100;

    int Notes[MaxNoteCount];
    unsigned short NoteDurations[MaxNoteCount];
    unsigned short NoteGaps[MaxNoteCount - 1];

    int nextNoteIndex = 0;

    void PlayRecorded()
    {
        if (IsRecording || nextNoteIndex == 0)
            return;

        StatusLeds::SetLed(LED_PLAYING, true);
        Serial.print("Playing recorded // Note Count: ");
        Serial.println(nextNoteIndex);

        for (int i = 0; i < nextNoteIndex; i++)
        {
            int note = Notes[i];
            int duration = NoteDurations[i];

            Serial.println("Note Index: " + String(i) + " // Duration: " + String(duration) + "// Note: " + String(note));

            NotePlayer::PlayNoteSync(note, duration);
            if (i != nextNoteIndex - 1)
            {
                Serial.println("Delay: " + String(NoteGaps[i]) + "\n");

                delay(NoteGaps[i]);
            }
        }

        StatusLeds::SetLed(LED_PLAYING, false);
    }

    void StartRecording()
    {
        if (IsRecording)
            return;
        nextNoteIndex = 0;
        IsRecording = true;
        StatusLeds::SetLed(LED_RECORDSTATUS, true);
        RecordingStartMilis = millis();
    }

    void StopRecording()
    {
        if (!IsRecording)
            return;
        IsRecording = false;

        if (nextNoteIndex == 0)
            StatusLeds::SetLed(LED_RECORDSTATUS, false);
        else
            StatusLeds::BlinkLed(LED_RECORDSTATUS, 5, 100);
    }

    unsigned long PreviousNoteEndOffset = 0;
    unsigned long NoteStartOffset = 0;
    int CurrentNote = -1;

    void NoteBegin(int Note)
    {
        if (!IsRecording)
            return;

        NoteStartOffset = millis() - RecordingStartMilis;
        CurrentNote = Note;
    }

    void NoteEnd()
    {
        if (!IsRecording)
            return;

        unsigned long NoteEndOffset = millis() - RecordingStartMilis;
        unsigned long NoteDuration = NoteEndOffset - NoteStartOffset;
        Serial.println(NoteDuration);

        if (NoteDuration == 0)
        {
            Serial.println("0 DURATION DETECTED");

            return;
        }

        if (NoteDuration > UINT16_MAX)
        {
            StopRecording();
            return;
        }

        Notes[nextNoteIndex] = CurrentNote;
        NoteDurations[nextNoteIndex] = NoteDuration;

        if (nextNoteIndex != 0)
        {
            unsigned long NoteGap = NoteStartOffset - PreviousNoteEndOffset;

            if (NoteGap > UINT16_MAX)
            {
                StopRecording();
                return;
            }

            NoteGaps[nextNoteIndex - 1] = NoteGap;
        }

        PreviousNoteEndOffset = NoteEndOffset;
        nextNoteIndex++;

        if (nextNoteIndex == MaxNoteCount)
        {
            NotePlayer::StopNote();
            StopRecording();
        }
    }

}