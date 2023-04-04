#pragma once

#include <shared/packet_types.hpp>

#include <QTcpSocket>

#include <memory>

class Client_2048;

// code that deals with client networking logic with server.
class ClientNetwork: public QObject
{
    Q_OBJECT

public:
    ClientNetwork(Client_2048 *owner);

    void  ConnectToServer();

    void  DisconnetFromServer();

    void  RequestRecordsFromServer();

    const char* ReadRecievedData();

public slots:
    void  ConnectionStablished();

    void  RecievedPacket();

    void  ConnectionDestroyed();

private:
    template<typename Data, typename Type>
    void  SendPacket(const Packet<Data, Type> &packet)
    {
        m_socket->write(packet);
        m_socket->waitForReadyRead(500);
    }

private:
    std::unique_ptr<QTcpSocket>  m_socket;
    Client_2048                 *m_owner;
};
