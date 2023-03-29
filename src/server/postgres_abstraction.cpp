#include "postgres_abstraction.hpp"

#include <utils/logger.hpp>

PGConnectionWrapper::PGConnectionWrapper(PGconn *connection)
{
    if (connection)
    {
        m_connection = connection;
    }
}

PGConnectionWrapper::PGConnectionWrapper(PGConnectionWrapper &&other)
{
    *this = std::forward<PGConnectionWrapper>(other);
}

PGConnectionWrapper& PGConnectionWrapper::operator=(PGConnectionWrapper &&other)
{
    if (other.m_connection)
    {
        m_connection       = other.m_connection;
        other.m_connection = nullptr;
    }
    else
    {
        LOG_FATAL("attempted to set a PGConnection object with another invalid ( not connected ) PGConnection object");
    }

    return *this;
}

PGConnectionWrapper::~PGConnectionWrapper()
{
    PQfinish(m_connection);
}

DataBaseConnectionStatus  PGConnectionWrapper::Connect(const QString &database, const QString &user_name, const QString &user_password)
{
    QString  full_request = "user=" + user_name;

    if (!(user_password.isEmpty()))
    {
        full_request += " pass=" + user_password;
    }

    full_request += " dbname=" + database;

    return Connect(full_request);
}

DataBaseConnectionStatus  PGConnectionWrapper::Connect(const QString &request)
{
    m_connection = PQconnectdb(request.toLatin1());

    auto  status = ConvertStatus(m_connection);

    SetStatus(status);

    return status;
}

PGSQLResult  PGConnectionWrapper::ExecuteSQL(const QString &str)
{
}

DataBaseConnectionStatus  PGConnectionWrapper::ConvertStatus(PGconn *connection) const
{
    auto  status = PQstatus(connection);

    switch (status)
    {
    case CONNECTION_OK:

        return DataBaseConnectionStatus::OK;
    case CONNECTION_AUTH_OK:

        return DataBaseConnectionStatus::AUTH_OK;
    case CONNECTION_MADE:

        return DataBaseConnectionStatus::MADE;
    case CONNECTION_STARTED:

        return DataBaseConnectionStatus::STARTED;
    case CONNECTION_BAD:

        return DataBaseConnectionStatus::BAD;
    case CONNECTION_AWAITING_RESPONSE:

        return DataBaseConnectionStatus::AWAITING_RESPONSE;
    case CONNECTION_CHECK_STANDBY:

        return DataBaseConnectionStatus::CHECK_STANDBY;
    case CONNECTION_CHECK_WRITABLE:

        return DataBaseConnectionStatus::CHECK_WRITABLE;
    case CONNECTION_CHECK_TARGET:

        return DataBaseConnectionStatus::CHECK_TARGET;
    case CONNECTION_CONSUME:

        return DataBaseConnectionStatus::CONSUME;
    case CONNECTION_GSS_STARTUP:

        return DataBaseConnectionStatus::GSS_STARTUP;
    case CONNECTION_SSL_STARTUP:

        return DataBaseConnectionStatus::SSL_STARTUP;
    case CONNECTION_NEEDED:

        return DataBaseConnectionStatus::NEEDED;
    case CONNECTION_SETENV:

        return DataBaseConnectionStatus::SETENV;
    }
}
