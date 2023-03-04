#include "application.hpp"
#include "applicationlayouts.hpp"

#include "logger.hpp"

// Application_2048 *app = nullptr;

Application_2048::Application_2048(int &argc, char **argv):
  QApplication(argc, argv), m_window(nullptr, this), m_mainmenu_layout(std::make_unique<MainMenuLayout>(this)),
  m_game_layout(std::make_unique<GameLayout>(this)), m_scoreboard_layout(std::make_unique<ScoreBoardLayout>(this))
{
  m_window.m_main_menu_screen->setLayout(m_mainmenu_layout.get());
  m_window.m_score_screen->setLayout(m_scoreboard_layout.get());
  m_window.m_game_screen->setLayout(m_game_layout.get());
}

qint32  Application_2048::Start()
{
  m_window.show();

  HandleAppEvent(Application_2048_Event::START_MAIN_MENU);

  return exec();
}

void  Application_2048::HandleAppEvent(Application_2048_Event event)
{
  switch (event)
  {
  case Application_2048_Event::NONE:
    break;

  case Application_2048_Event::START_MAIN_MENU:

    if (m_state == Application_2048_State::GAME)
    {
      m_game.ReStart();
    }

    DisplayMainMenu();

    break;

  case Application_2048_Event::START_GAME:

    if (m_state != Application_2048_State::GAME)
    {
      StartGame();
    }

    break;

  case Application_2048_Event::SHOW_SCORES:

    if (m_state != Application_2048_State::GAME)
    {
      DisplayScores();
    }

    break;

  case Application_2048_Event::SHIFT_LEFT:

    if (m_state == Application_2048_State::GAME)
    {
      m_game.Shift(ShiftDirection::LEFT);
      UpdateGameScreen();
    }

    break;

  case Application_2048_Event::SHIFT_UP:

    if (m_state == Application_2048_State::GAME)
    {
      m_game.Shift(ShiftDirection::UP);
      UpdateGameScreen();
    }

    break;

  case Application_2048_Event::SHIFT_RIGHT:

    if (m_state == Application_2048_State::GAME)
    {
      m_game.Shift(ShiftDirection::RIGHT);
      UpdateGameScreen();
    }

    break;
  case Application_2048_Event::SHIFT_DOWN:

    if (m_state == Application_2048_State::GAME)
    {
      m_game.Shift(ShiftDirection::DOWN);
      UpdateGameScreen();
    }

    break;

  case Application_2048_Event::UPDATE_SLOTS:

    if (m_state == Application_2048_State::GAME)
    {
      UpdateGameScreen();
    }

    break;

  case Application_2048_Event::RESET_GAME:

    if (m_state == Application_2048_State::GAME)
    {
      m_game.ReStart();
      UpdateGameScreen();
    }

    break;

  case Application_2048_Event::EXIT:

    if (m_state == Application_2048_State::MAIN_MENU)
    {
      exit();
    }
    else if (m_state == Application_2048_State::GAME)
    {
      m_game.ReStart();
      m_game_layout->Reset();
      DisplayMainMenu();
    }
    else if (m_state == Application_2048_State::OPTIONS)
    {
      DisplayMainMenu();
    }

    break;
  }
}

void  Application_2048::UpdateGameScreen()
{
  m_game_layout->DisplaySlotValues(m_game.GetSlots());
}

void  Application_2048::DisplayMainMenu()
{
  m_state = Application_2048_State::MAIN_MENU;
  m_window.DisplayView(Application_2048_View::MAIN_MENU);
}

void  Application_2048::StartGame()
{
  m_state = Application_2048_State::GAME;
  m_window.DisplayView(Application_2048_View::GAME);
  m_game.Start();
  UpdateGameScreen();
}

void  Application_2048::DisplayScores()
{
  m_state = Application_2048_State::OPTIONS;
  m_window.DisplayView(Application_2048_View::SCORES);
  // PlayerRecords  player_records = ReadPlayerRecords();
}
