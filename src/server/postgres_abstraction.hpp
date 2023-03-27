#pragma once

#include <postgresql/libpq-fe.h>
#include <QString>

enum class DataBaseConnectionStatus
{
    OK,                         // connection stablished.
    AUTH_OK,
    MADE,
    STARTED,
    BAD,
    AWAITING_RESPONSE,
    CHECK_STANDBY,
    CHECK_WRITABLE,
    CHECK_TARGET,
    CONSUME,
    GSS_STARTUP,
    SSL_STARTUP,
    NEEDED,
    SETENV,
    NOT_SETUP                   // invalid state. connection has not been made yet.
};

class PGConnectionWrapper
{
public:
    PGConnectionWrapper(PGconn *connection = nullptr);

    PGConnectionWrapper(const PGConnectionWrapper &other) = delete;

    PGConnectionWrapper(PGConnectionWrapper &&other);

    PGConnectionWrapper& operator=(const PGConnectionWrapper &other) = delete;

    PGConnectionWrapper& operator=(PGConnectionWrapper &&other);

    ~PGConnectionWrapper();

    inline DataBaseConnectionStatus  GetConnectionStatus() const
    {
        return m_status;
    }

    DataBaseConnectionStatus  Connect(const QString &database, const QString &user_name, const QString &user_password = { });

    DataBaseConnectionStatus  Connect(const QString &request);

    inline const std::string  GetError() const
    {
        char *message = PQerrorMessage(m_connection);

        return message;
    }

    inline operator bool() const {
        return IsConnected();
    }

    inline operator PGconn *() const
    {
        return m_connection;
    }

    inline bool  IsConnected() const
    {
        return m_connection != nullptr;
    }

private:
    inline void  SetStatus(DataBaseConnectionStatus status)
    {
        m_status = status;
    }

    // converts a postgresql ConnStatusType to our own DataBaseConnectionStatus.
    DataBaseConnectionStatus  ConvertStatus(PGconn *connection) const;

private:
    PGconn                   *m_connection = nullptr;
    DataBaseConnectionStatus  m_status     = DataBaseConnectionStatus::NOT_SETUP;
};
