#pragma once

#include "gamelogic.hpp"
#include "gamewindow.hpp"
#include "applicationlayouts.hpp"
#include "applicationevents.hpp"
#include <shared/playerscore.hpp>

#include <QApplication>

enum class Application_2048_State
{
    MAIN_MENU,
    REGISTER_MENU,
    GAME,
    SCORES_MENU
};

class Application_2048: public QApplication
{
    Q_OBJECT

public:
    Application_2048(int &argc, char **argv);

    qint32  Start();

    void  HandleAppEvent(Application_2048_Event app_event);

    void  UpdateGameScreen();

    bool  CheckIfPlayerRecordExists(const QString &player_name);

private:
    void  DisplayMainMenu();

    void  StartGame();

    void  DisplayScores();

    void  StartRegisterMenu();

private:
    Application_2048_State                  m_state;
    ApplicationWindow                       m_window;
    GameLogic                               m_game;
    std::unique_ptr<MainMenuLayout>         m_mainmenu_layout;
    std::unique_ptr<GameLayout>             m_game_layout;
    std::unique_ptr<ScoreBoardLayout>       m_scoreboard_layout;
    std::unique_ptr<PlayerRegisteryLayout>  m_register_layout;
    std::optional<PlayerRecords>            m_players_datas;
};

// extern Application_2048 *app;
