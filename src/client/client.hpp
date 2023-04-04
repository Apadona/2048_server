#pragma once

#include "gamelogic.hpp"
#include "gamewindow.hpp"
#include "client_layouts.hpp"
#include "client_events.hpp"
#include "client_network.hpp"

#include <QApplication>
#include <QTcpSocket>

enum class Client_2048_State
{
    MAIN_MENU,
    REGISTER_MENU,
    GAME,
    SCORES_MENU
};

class Client_2048: public QApplication
{
    Q_OBJECT

public:
    Client_2048(int &argc, char **argv);

    qint32  Start();

    void  HandleAppEvent(Client_2048_Event app_event);

    void  UpdateGameScreen();

    bool  CheckIfPlayerRecordExists(const QString &player_name);

    void  SubmitPlayerRecordToServer(const PlayerRecord &record);

// public slots:
// void  ConnectionAccepted();

private:
    void  DisplayMainMenu();

    void  StartGame();

    void  DisplayScores();

    void  StartRegisterMenu();

private:
    Client_2048_State                       m_state;
    ApplicationWindow                       m_window;
    GameLogic                               m_game;
    std::unique_ptr<MainMenuLayout>         m_mainmenu_layout;
    std::unique_ptr<GameLayout>             m_game_layout;
    std::unique_ptr<ScoreBoardLayout>       m_scoreboard_layout;
    std::unique_ptr<PlayerRegisteryLayout>  m_register_layout;
    std::optional<PlayerRecords>            m_players_datas;
    ClientNetwork                           m_network;
};

// extern Client_2048 *app;
