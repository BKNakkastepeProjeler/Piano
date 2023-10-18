#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

#include "Music\Notes.h"
#include "Music\NoteRecorder.h"

namespace LCD
{
    LiquidCrystal_I2C disp(0x3F,16,2);

    void LCDInit()
    {
        disp.init();
        disp.backlight();
        disp.clear();
    }


    void printCenter(uint8_t row, String text)
    {
        int textLength = text.length();

        if(textLength == 0 || textLength > 16) return;

        disp.setCursor(textLength % 2 == 0 ? (16 - textLength) / 2 : (15 - textLength) / 2,row);
        disp.print(text);
    }

    void clearRow(uint8_t row)
    {
        disp.setCursor(0,row);
        disp.print("                ");
    }


    void displayOctave()
    {
        clearRow(0);
        printCenter(0,"Oktav: " + String(Notes::getOctaveIndex() + 1));
    }

    void displayRecordState(uint8_t state)
    {
        clearRow(1);

        switch (state)
        {
            case 0: break;

            case 1: printCenter(1,"Kaydediliyor.."); break;

            case 2: printCenter(1, "Kaydedildi"); break;

            case 3: clearRow(0); printCenter(0,"Oynatiliyor..."); break;

            case 4: displayOctave(); break;
        }
    }
}