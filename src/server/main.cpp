#include "server.hpp"

int  main(int argc, char **argv)
{
    Logger::Init();

    Server_2048  server(argc, argv);

    return server.exec();
}
