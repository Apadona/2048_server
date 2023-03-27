#pragma once

#include <QApplication>

#include "postgres_abstraction.hpp"

#include <shared/playerscore.hpp>

class Server_2048: public QApplication
{
    Q_OBJECT

public:
    Server_2048(int &argc, char **argv);

    Server_2048(const Server_2048 &other) = delete;

    Server_2048(Server_2048 &&other) = delete;

    Server_2048& operator=(const Server_2048 &other) = delete;

    Server_2048& operator=(Server_2048 &&other) = delete;

    ~Server_2048();

    qint32  Start();

    void  StablishConnection();

private:
    void  ReadAllPlayerRecords();

private:
    PGConnectionWrapper  m_database;
    PlayerRecords        m_records;
};
