#include <Arduino.h>

#include "Pinout.h"

#include "Input\InputHandler.h"
#include "Music\NotePlayer.h"
#include "Music\NoteRecorder.h"
#include "Display\LCD.h"
#include "Music\Notes.h"

void setup()
{
  Serial.begin(9600);

  LCD::LCDInit();
  InputHandler::InputHandlerInit();



  LCD::displayOctave();
}

void checkRecordButton()
{  
  
  InputHandler::ButtonState recordButtonState = InputHandler::GetButtonState(BTN_RECORD);
  if (recordButtonState != InputHandler::None)
  {
    Serial.println("Rec");
    if (recordButtonState == InputHandler::Hold) NoteRecorder::PlayRecorded();
    else
    {
      switch (NoteRecorder::IsRecording)
      {
      case true:
        NoteRecorder::StopRecording();
        break;
      case false:
        NoteRecorder::StartRecording();
        break;
      }
    }
  }

}

void checkOctaveButtons()
{
  InputHandler::ButtonState increaseOctaveButtonState = InputHandler::GetButtonState(BTN_INCREASEOCTAVE);

  if(increaseOctaveButtonState != InputHandler::None)
  {
    Serial.println("Inc Oct Btn");
    Notes::setOctaveByIndex(Notes::getOctaveIndex() + 1);
    return;
  }

  InputHandler::ButtonState decreaseOctaveButtonState = InputHandler::GetButtonState(BTN_DECREASEOCTAVE);

  if(decreaseOctaveButtonState != InputHandler::None)
  {
    Serial.println("Dec Oct Btn");
    Notes::setOctaveByIndex(Notes::getOctaveIndex() - 1);
    return;
  }
}



void loop()
{
  checkOctaveButtons();

  checkRecordButton();

  NotePlayer::NoteLoop();
}