#pragma once

namespace NoteRecorder
{
    extern bool IsRecording;
    void StartRecording();
    void StopRecording();
    void NoteBegin(int Note);
    void NoteEnd();
}