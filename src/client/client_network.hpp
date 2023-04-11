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

    PlayerRecords  ReadRecievedRecords();

    bool  IsConnected() const
    {
        return m_socket->isOpen();
    }

public slots:
    void  ConnectionStablished();

    void  RecievedPacket();

    void  ConnectionDestroyed();

private:
    void  SendPacket(Packet &packet)
    {
        auto size = packet.Size();
        m_socket->write(packet, size);
        m_socket->waitForReadyRead(200);
    }

    template<typename Data, typename Type>
    void  ProcessPacket(const Packet &packet)
    {
    }

private:
    std::unique_ptr<QTcpSocket>  m_socket;
    Client_2048                 *m_owner;
    Packet                       m_recieved_packet;     // buffer for processing network packets.
};
