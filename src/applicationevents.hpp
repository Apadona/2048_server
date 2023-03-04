#pragma once

// events which are specific to our application.
enum class Application_2048_Event
{
  NONE, // invalid event, does nothing.
  START_MAIN_MENU,
  START_GAME,
  SHOW_SCORES,
  SHIFT_LEFT,
  SHIFT_UP,
  SHIFT_RIGHT,
  SHIFT_DOWN,
  UPDATE_SLOTS,
  RESET_GAME,
  EXIT
};
