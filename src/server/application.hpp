#pragma once

#include <QApplication>

class Server_2048 : public QApplication
{
    Q_OBJECT

public:
    Server_2048( int& argc, char** argv );

    qint32 Start();

private:

};
