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
  bool recordButtonState = InputHandler::GetButtonState(BTN_RECORD);
  if(recordButtonState)
  {

    switch (NoteRecorder::IsRecording)
    {
      case true: NoteRecorder::StopRecording(); break;
      case false: NoteRecorder::StartRecording(); break;
    }

    delay(300);
  }
  
  NotePlayer::NoteLoop();
}