#include "application.hpp"
#include "applicationlayouts.hpp"
#include "logger.hpp"
#include "csscolors.hpp"

Application_2048::Application_2048(int &argc, char **argv):
  QApplication(argc, argv), m_window(nullptr, this), m_mainmenu_layout(std::make_unique<MainMenuLayout>(this)),
  m_game_layout(std::make_unique<GameLayout>(this)), m_scoreboard_layout(std::make_unique<ScoreBoardLayout>(this)),
  m_register_layout(std::make_unique<PlayerRegisteryLayout>(this))
{
  m_window.AddLayout(m_mainmenu_layout.get(), Application_2048_View::MAIN_MENU);
  m_window.AddLayout(m_register_layout.get(), Application_2048_View::REGISTER);
  m_window.AddLayout(m_game_layout.get(), Application_2048_View::GAME);
  m_window.AddLayout(m_scoreboard_layout.get(), Application_2048_View::SCORES);

  // m_players_datas = ReadPlayerRecords();

  _2048_CSSColors::Init();
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

  case Application_2048_Event::START_REGISTER_MENU:

    if (m_state == Application_2048_State::MAIN_MENU)
    {
      StartRegisterMenu();
    }

    break;

  case Application_2048_Event::START_GAME:

    if (m_state == Application_2048_State::REGISTER_MENU)
    {
      m_register_layout->EmptyMessage();
      StartGame();
    }

    break;

  case Application_2048_Event::SHOW_SCORES:

    if (m_state != Application_2048_State::GAME)
    {
      DisplayScores();
    }

    break;

  case Application_2048_Event::CHECK_INPUTTED_NAME:

    if (m_state == Application_2048_State::REGISTER_MENU)
    {
      // TODO: must check against player database.
      QString  name = m_register_layout->GetInputtedName();

      if (name.isEmpty())
      {
        m_register_layout->EmptyMessage();
      }
      else if (CheckIfPlayerRecordExists(name))
      {
        m_register_layout->DisplayString(name + " is already submitted", true);
      }
      else
      {
        m_register_layout->DisplayString(name + " can be submitted", false);
      }

      break;
    }

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
      m_game.Start();
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
    else if (m_state == Application_2048_State::SCORES_MENU)
    {
      DisplayMainMenu();
    }
    else if (m_state == Application_2048_State::REGISTER_MENU)
    {
      m_register_layout->EmptyMessage();
      DisplayMainMenu();
    }

    break;
  }
}

void  Application_2048::UpdateGameScreen()
{
  m_game_layout->DisplaySlotValues(m_game.GetSlots());
}

bool  Application_2048::CheckIfPlayerRecordExists(const QString &player_name)
{
  if (!player_name.isEmpty())
  {
    if (m_players_datas.has_value())
    {
      auto &player_records = m_players_datas.value();

      for (auto &i : player_records)
      {
        if (i.m_name == player_name)
        {
          return false;
        }
      }

      return true;
    }
  }

  return false;
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
  m_state = Application_2048_State::SCORES_MENU;
  m_window.DisplayView(Application_2048_View::SCORES);
  // m_scoreboard_layout->DisplayScores(m_player_datas);
}

void  Application_2048::StartRegisterMenu()
{
  m_state = Application_2048_State::REGISTER_MENU;
  m_window.DisplayView(Application_2048_View::REGISTER);
}
