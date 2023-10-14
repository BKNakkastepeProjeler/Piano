#pragma once

namespace InputHandler
{   
    enum ButtonState
    {
        None,
        Down,
        Hold
    };

    bool GetButtonValue(int PIN);
    bool GetNoteState(int note);
    void InputHandlerInit();
    ButtonState GetButtonState(int PIN);
}
