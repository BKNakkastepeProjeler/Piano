#pragma once

namespace Notes
{
    void setOctaveByIndex(int octIndex);

    int getOctaveIndex();

    int getNote(int octaveNoteIndex);

    const int minOctaveIndex;
    const int maxOctaveIndex;
    const int minNoteIndex;
    const int maxNoteIndex;
}