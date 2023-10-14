#pragma once

#define NOTE_C 262
#define NOTE_D 294
#define NOTE_E 330
#define NOTE_F 349
#define NOTE_G 392
#define NOTE_A 440
#define NOTE_B 493

namespace NotePlayer
{
    void NoteLoop();

    void PlayNoteSync(int note, unsigned long duration);
    void StopNote();
}