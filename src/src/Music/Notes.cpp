#include "Display\LCD.h"

namespace Notes
{    
    
    const int allNotes[] = {
        33,
        37,
        41,
        44,
        49,
        55,
        62,

        65,
        73,
        82,
        87,
        98,
        110,
        123,

        131,
        147,
        165,
        175,
        196,
        220,
        247,

        262,
        294,
        330,
        349,
        392,
        440,
        494,

        523,
        587,
        659,
        698,
        784,
        880,
        988,

        1047,
        1175,
        1319,
        1397,
        1568,
        1760,
        1976,

        2093,
        2349,
        2637,
        2794,
        3136,
        3520,
        3951};

    const int minOctaveIndex = 0;
    const int maxOctaveIndex = 6;


    int octaveIndex = 4;


    void setOctaveByIndex(int octIndex)
    {
        if(octIndex < minOctaveIndex || octIndex > maxOctaveIndex) return;

        octaveIndex = octIndex;
        LCD::displayOctave();
    }

    int getOctaveIndex()
    {
        return octaveIndex;
    }

    int getNote(int octaveNoteIndex)
    {
        if(octaveIndex < 0 || octaveIndex > 6) return 0;

        int noteIndex = (octaveIndex * 7) + octaveNoteIndex;

        return allNotes[noteIndex];
    }

}