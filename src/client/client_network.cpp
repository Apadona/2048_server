#include "client_network.hpp"
#include "client.hpp"

#include <utils/logger.hpp>

#include <QHostAddress>

ClientNetwork::ClientNetwork(Client_2048 *owner):
    m_socket(std::make_unique<QTcpSocket>()),
    m_owner(owner)
{
    connect(m_socket.get(), &QTcpSocket::connected, this, &ClientNetwork::ConnectionStablished);
    connect(m_socket.get(), &QTcpSocket::disconnected, this, &ClientNetwork::ConnectionDestroyed);
    connect(m_socket.get(), &QTcpSocket::readyRead, this, &ClientNetwork::RecievedPacket);
}

void  ClientNetwork::ConnectToServer()
{
    m_socket->connectToHost(QHostAddress::Any, 10000);
}

void  ClientNetwork::DisconnetFromServer()
{
    m_socket->close();
}

void  ClientNetwork::RequestRecordsFromServer()
{
    Packet  packet;

    packet.SetType(PacketTypes::REQUEST_RECORDS);

    SendPacket(packet);
}

PlayerRecords  ClientNetwork::ReadRecievedRecords()
{
    PlayerRecords  records;
    PlayerRecord   temp;

    if (m_recieved_packet)
    {
        if (m_recieved_packet.GetType<PacketTypes>() == PacketTypes::RECIEVE_RECORDS)
        {
            m_recieved_packet >> records;
        }
    }

    return std::move(records);
}

void  ClientNetwork::ConnectionStablished()
{
    LOG_INFO("connection to server stablished!");
}

void  ClientNetwork::RecievedPacket()
{
    auto *socket = qobject_cast<QTcpSocket *>(sender());

    m_recieved_packet = socket->readAll();

    m_recieved_packet.SetType(PacketTypes::RECIEVE_RECORDS);

    if (m_recieved_packet)
    {
        m_owner->HandleAppEvent(Client_2048_Event::RECIEVED_DATA_FROM_SERVER);
    }
}

void  ClientNetwork::ConnectionDestroyed()
{
    LOG_INFO("disconnected from the server.");
}
