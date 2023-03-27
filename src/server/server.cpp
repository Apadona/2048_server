#include "server.hpp"

#include <utils/logger.hpp>

Server_2048::Server_2048(int &argc, char **argv):
    QApplication(argc, argv),
    m_database(nullptr)
{
    Start();
}

Server_2048::~Server_2048()
{
}

qint32  Server_2048::Start()
{
    m_database.Connect("user=barkhordar dbname=game_2048");

    if (m_database.GetConnectionStatus() == DataBaseConnectionStatus::BAD)
    {
        LOG_FATAL("could not connect to the server! Reason:", m_database.GetError());

        return -1;
    }

    return 0;
}
