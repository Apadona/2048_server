#pragma once

#include <QApplication>

#include "postgres_abstraction.hpp"
#include "database.hpp"
#include "server_network.hpp"

#include <shared/player_record.hpp>

class Server_2048: public QApplication
{
    Q_OBJECT

    friend class ServerNetwork;

public:
    Server_2048(int &argc, char **argv);

    Server_2048(const Server_2048 &other) = delete;

    Server_2048(Server_2048 &&other) = delete;

    Server_2048& operator=(const Server_2048 &other) = delete;

    Server_2048& operator=(Server_2048 &&other) = delete;

    ~Server_2048();

    qint32  Start();

private:
    DataBase_2048  m_database;
    ServerNetwork  m_network;
};
