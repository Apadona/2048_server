#include "database.hpp"

#include <utils/logger.hpp>

bool  DataBase_2048::Connect(const QString &user_name, const QString &database, const QString &user_password)
{
    m_connection.Connect(database, user_name, user_password);

    if (m_connection.IsConnected())
    {
        LOG_INFO("Database connection stablished succesfully.");

        FetchRecordsFromDataBase();

        return true;
    }

    LOG_WARNING("Could not stablish a connection to database. Reason:" + m_connection.GetError());

    return false;
}

DataBaseConnectionStatus  DataBase_2048::GetConnectionStatus() const
{
    return m_connection.GetConnectionStatus();
}

bool  DataBase_2048::IsEmpty() const
{
    return m_records.empty();
}

void  DataBase_2048::FetchRecordsFromDataBase()
{
    auto  sql_result = m_connection.ExecuteSQL("SELECT * FROM player_database");

    if (sql_result)
    {
// for( auto str : sql_result )
    }
}
