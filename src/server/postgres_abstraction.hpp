#pragma once

#include <postgresql/libpq-fe.h>
#include <QString>
#include <type_traits>
#include <string>
#include <iterator>

enum class DataBaseConnectionStatus
{
    OK,                                                                                                         // connection stablished.
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
    NOT_SETUP,                                                                                                  // invalid state. connection has not been made
                                                                                                                // yet.

    NONE
};

enum class QueryResultType
{
    EMPTY_QUERY = 0,

    /* empty query string was executed
     */
    COMMAND_OK,

    /* a query command that doesn't return
     * anything was executed properly by the
     * backend */
    TUPLES_OK,

    /* a query command that returns tuples was
     * executed properly by the backend, PGresult
     * contains the result tuples */
    COPY_OUT,

    /* Copy Out data transfer in progress
     */
    COPY_IN,

    /* Copy In data transfer in progress
     */
    BAD_RESPONSE,

    /* an unexpected response was recv'd from the
     * backend */
    NONFATAL_ERROR,                                                                                                               /* notice or warning message */
    FATAL_ERROR,                                                                                                                  /* query failed */
    COPY_BOTH,

    /* Copy In/Out data transfer in progress
     */
    SINGLE_TUPLE,

    /* single tuple from larger resultset
     */
    PIPELINE_SYNC,

    /* pipeline synchronization point
     */
    PIPELINE_ABORTED,

    /* Command didn't run because of an abort
     */

    NONE
};

class PGSQLResult
{
public:
    PGSQLResult() = default;

    PGSQLResult(PGresult *result);

// PGSQLResult(const QString &query);

    ~PGSQLResult();

    PGSQLResult(const PGSQLResult &other) = delete;

    PGSQLResult(PGSQLResult &&other);

    PGSQLResult& operator=(const PGSQLResult &other) = delete;

    PGSQLResult& operator=(PGSQLResult &&other);

    std::string::iterator  begin();

    std::string::iterator  end();

    inline QueryResultType  GetStatus() const
    {
        return m_query_result;
    }

    inline operator bool() const
    {
        return m_result != nullptr && GetStatus() != QueryResultType::EMPTY_QUERY;
    }
    inline bool  operator!() const
    {
        return !bool(*this);
    }

    inline quint32  GetRows() const
    {
        return PQntuples(m_result);
    }

    void  ClearQuery();

private:
    QueryResultType  ConvertStatus(PGresult *postgres_status);

    inline void  SetStatus(QueryResultType query_result)
    {
        m_query_result = query_result;
    }

private:
    QueryResultType  m_query_result = QueryResultType::NONE;
    PGresult        *m_result       = nullptr;
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

    PGSQLResult  ExecuteSQL(const QString &str);

// template<typename ... Args>
// PGSQLResult  ExecuteSQL(const QString &Str, Args && ... args);

    inline const std::string  GetError() const
    {
        char *message = PQerrorMessage(m_connection);

        return message;
    }

    inline operator bool() const
    {
        return IsConnected();
    }

    inline operator PGconn *() const
    {
        return m_connection;
    }

    inline bool  IsConnected() const
    {
        return m_connection != nullptr && GetConnectionStatus() != DataBaseConnectionStatus::BAD;
    }

private:
    inline void  SetStatus(DataBaseConnectionStatus status)
    {
        m_status = status;
    }

    // converts a postgresql ConnStatusType to our own DataBaseConnectionStatus.
    DataBaseConnectionStatus  ConvertStatus(PGconn *postgres_connection) const;

private:
    PGconn                   *m_connection = nullptr;
    qint32                    m_version;
    QString                   m_user_name;
    QString                   m_user_password;
    DataBaseConnectionStatus  m_status = DataBaseConnectionStatus::NONE;
};
