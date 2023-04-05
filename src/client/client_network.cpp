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
    RequestRecordsPacket  packet;

    packet.SetType(PacketTypes::REQUEST_RECORDS);

    SendPacket(packet);
}

const char * ClientNetwork::ReadRecievedData()
{
    return m_socket->readAll();
}

void  ClientNetwork::ConnectionStablished()
{
    LOG_INFO("connection to server stablished!");
}

void  ClientNetwork::RecievedPacket()
{
    m_owner->HandleAppEvent(Client_2048_Event::RECIEVED_DATA_FROM_SERVER);
}

void  ClientNetwork::ConnectionDestroyed()
{
    LOG_INFO("disconnected from the server.");
}
