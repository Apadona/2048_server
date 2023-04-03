#include "server.hpp"

#include <utils/logger.hpp>

Server_2048::Server_2048(int &argc, char **argv):
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

    PlayerRecord  test_record;
    test_record.m_name  = "ricardo";
    test_record.m_score = 200;
    m_database.SubmitRecord(test_record);
    m_database.Print();

    m_database.RemoveRecord(test_record);
    m_database.Print();

    return 0;
}
