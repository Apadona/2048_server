#pragma once

// events which are specific to our application.
enum class Client_2048_Event
{
    NONE, // null event, does nothing.
    START_MAIN_MENU,
    START_REGISTER_MENU,
    START_GAME,
    SHOW_SCORES,
    CHECK_INPUTTED_NAME,
    SHIFT_LEFT,
    SHIFT_UP,
    SHIFT_RIGHT,
    SHIFT_DOWN,
    UPDATE_SLOTS,
    RESET_GAME,
    RECIEVED_DATA_FROM_SERVER,
    EXIT
};
