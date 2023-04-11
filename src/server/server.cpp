#include "server.hpp"

#include <utils/logger.hpp>

Server_2048::Server_2048(int &argc, char **argv):
    m_network(this),
    QApplication(argc, argv)
{
    Start();
}

Server_2048::~Server_2048()
{
}

qint32  Server_2048::Start()
{
    m_database.Connect("barkhordar", "game_2048");

    if (!m_database)
    {
        return -1;
    }

    m_database.Print();

    m_network.Start();

    return 0;
}
