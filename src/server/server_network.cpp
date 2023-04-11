#include "server_network.hpp"
#include "server.hpp"

#include <utils/logger.hpp>

#include <QDebug>

ServerNetwork::ServerNetwork(Server_2048 *owner_app):
    m_owner_app(owner_app)
{
    connect(&m_server, &QTcpServer::newConnection, this, &ServerNetwork::NewIncommingConnection);
}

void  ServerNetwork::Start()
{
    m_server.listen(QHostAddress::Any, 10000);
}

void  ServerNetwork::Disconnect()
{
    m_server.close();
}

void  ServerNetwork::ProcessIncomingPacket(Packet &packet, QTcpSocket *socket)
{
    PlayerRecord  record;

    auto type = packet.GetType<PacketTypes>();

    switch (type)
    {
    case PacketTypes::INVALID:
        LOG_WARNING("packet type of INVALID sent to server by client which should not be sent to anything!");
        break;

    case PacketTypes::RECIEVE_RECORDS:
        LOG_WARNING("packet type of RECIEVE_RECORDS should only be sent by server to client not the opposite!");
        break;

    case PacketTypes::SUBMIT_RECORD:
        packet >> record;
        m_owner_app->m_database.SubmitRecord(record);
        break;

    case PacketTypes::REQUEST_RECORDS:
        Packet  sending_packet;
        sending_packet.SetType(PacketTypes::RECIEVE_RECORDS);
        auto &data = m_owner_app->m_database.GetRecords();
        sending_packet << data;
        socket->write(sending_packet, sending_packet.Size());
        socket->waitForBytesWritten();
        break;
    }
}

void  ServerNetwork::NewIncommingConnection()
{
    auto *socket = m_server.nextPendingConnection();

    m_connections.emplace_back(socket);

    connect(socket, &QTcpSocket::disconnected, this, &ServerNetwork::ConnectionClosed);
    connect(socket, &QTcpSocket::readyRead, this, &ServerNetwork::RecievedPacket);

    LOG_INFO("new connection stablished:", socket);
}

void  ServerNetwork::RecievedPacket()
{
    auto *socket = qobject_cast<QTcpSocket *>(sender());

    if (!socket)
    {
        LOG_FATAL("recieved packet's sender is not known!");

        return;
    }

    if (std::find(m_connections.begin(), m_connections.end(), socket) == std::end(m_connections))
    {
        LOG_CRITICAL("the client that sent data to the server has not registered in the server!");

        return;
    }

    LOG_INFO("recieved data from client:", socket);

    QByteArray data = socket->readAll();

    Packet      recieved_packet(data);

    ProcessIncomingPacket(recieved_packet, socket);
}

void  ServerNetwork::ConnectionClosed()
{
    auto *socket = qobject_cast<QTcpSocket *>(sender());

    LOG_INFO("connection closed:", socket);

    socket->deleteLater();
}
