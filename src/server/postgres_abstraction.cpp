#include "postgres_abstraction.hpp"

#include <utils/logger.hpp>

PGSQLResult::PGSQLResult(PGresult *result)
{
    if (result)
    {
        if (auto status = ConvertStatus(result); status != QueryResultType::FATAL_ERROR)
        {
            m_result = result;
            SetStatus(status);
        }
    }
}

PGSQLResult::PGSQLResult(PGSQLResult &&other)
{
    *this = std::forward<PGSQLResult>(other);
}

PGSQLResult& PGSQLResult::operator=(PGSQLResult &&other)
{
    if (this != &other)
    {
        m_result       = other.m_result;
        m_query_result = other.m_query_result;

        other.m_result       = nullptr;
        other.m_query_result = QueryResultType::NONE;
    }

    return *this;
}

PGSQLResult::~PGSQLResult()
{
    ClearQuery();
}

void  PGSQLResult::ClearQuery()
{
    PQclear(m_result);
}

QueryResultType  PGSQLResult::ConvertStatus(PGresult *postgres_query_result)
{
    auto  status = PQresultStatus(postgres_query_result);

    switch (status)
    {
    case PGRES_EMPTY_QUERY:

        return QueryResultType::EMPTY_QUERY;
    case PGRES_COMMAND_OK:

        return QueryResultType::COMMAND_OK;
    case PGRES_TUPLES_OK:

        return QueryResultType::TUPLES_OK;
    case PGRES_COPY_OUT:

        return QueryResultType::COPY_OUT;
    case PGRES_COPY_IN:

        return QueryResultType::COPY_IN;
    case PGRES_BAD_RESPONSE:

        return QueryResultType::BAD_RESPONSE;
    case PGRES_NONFATAL_ERROR:

        return QueryResultType::NONFATAL_ERROR;
    case PGRES_FATAL_ERROR:

        return QueryResultType::EMPTY_QUERY;
    case PGRES_COPY_BOTH:

        return QueryResultType::COPY_BOTH;
    case PGRES_SINGLE_TUPLE:

        return QueryResultType::SINGLE_TUPLE;
    case PGRES_PIPELINE_SYNC:

        return QueryResultType::PIPELINE_SYNC;
    case PGRES_PIPELINE_ABORTED:

        return QueryResultType::PIPELINE_ABORTED;
    }
}

QString  PGSQLResult::Get(quint32 row, quint32 column)
{
    return PQgetvalue(m_result, row, column);
}

PGConnectionWrapper::PGConnectionWrapper(PGconn *connection)
{
    if (connection)
    {
        m_connection = connection;
        m_version    = PQserverVersion(connection);
        m_user_name  = PQuser(connection);
        m_user_name  = PQdb(connection);
        m_user_name  = PQpass(connection);
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
    auto  _result = PQexec(m_connection, str.toLatin1());

    return PGSQLResult(_result);
}

DataBaseConnectionStatus  PGConnectionWrapper::ConvertStatus(PGconn *postgres_connection) const
{
    auto  status = PQstatus(postgres_connection);

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
