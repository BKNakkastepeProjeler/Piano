#include <Arduino.h>

#include "InputHandler.h"
#include "NotePlayer.h"

void setup()
{
  InputHandler::InputHandlerInit();
}

void loop()
{
  NotePlayer::NoteLoop();
}