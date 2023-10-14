#include <Arduino.h>

#include "InputHandler.h"
#include "StatusLeds.h"
#include "NotePlayer.h"
#include "NoteRecorder.h"
#include "Pinout.h"

void setup()
{
  Serial.begin(9600);

  StatusLeds::StatusLedsInit();
  InputHandler::InputHandlerInit();
}

void loop()
{
  InputHandler::ButtonState recordButtonState = InputHandler::GetButtonState(BTN_RECORD);
  if (recordButtonState != InputHandler::None)
  {
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

  NotePlayer::NoteLoop();
}