#pragma once

#include <shared/packet_types.hpp>

#include <QTcpServer>
#include <QTcpSocket>

#include <vector>

class Server_2048;

class ServerNetwork: public QObject
{
public:
    ServerNetwork(Server_2048 *owner_app);

    void  Start();

    void  Disconnect();

public slots:
    void  NewIncommingConnection();

    void  RecievedPacket();

    void  ConnectionClosed();

private:
    void  ProcessIncomingPacket(Packet &packet, QTcpSocket *socket);

private:
    QTcpServer                 m_server;
    std::vector<QTcpSocket *>  m_connections;                                 // sockets used to commiunicate with the connected client.
    Server_2048               *m_owner_app;
};
