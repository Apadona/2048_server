#include "application.hpp"

int main( int argc, char** argv )
{
    Server_2048 server(argc,argv);

    server.Start();

    return server.exec();
}
