#include "database.hpp"

#include <utils/logger.hpp>

#include <algorithm>

DataBase_2048::DataBase_2048(const QString &user_name, const QString &database, const QString &user_password)
{
    Connect(user_name, database, user_password);
}

bool  DataBase_2048::Connect(const QString &user_name, const QString &database, const QString &user_password)
{
    m_connection.Connect(database, user_name, user_password);

    if (m_connection.IsConnected())
    {
        LOG_INFO("Database connection stablished succesfully.");

        m_user_name     = user_name;
        m_user_password = user_password;
        m_database_name = database;

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

bool  DataBase_2048::SubmitRecord(const PlayerRecord &player_record)
{
    if (!player_record)
    {
        LOG_WARNING("attemp to submit an invalid player_record to server!");

        return false;
    }

    QString  sql_query = "INSERT INTO player_records VALUES ('" + player_record.m_name + "',"
                         + QString::number(player_record.m_score) + ")";
    auto  sql_result = m_connection.ExecuteSQL(sql_query);

    if (sql_result)
    {
        UpdateRecords();

        return true;
    }

    LOG_WARNING("sql query for submitting PlayerRecord didn't work.");

    return false;
}

void  DataBase_2048::RemoveRecord(const PlayerRecord &player_record)
{
    if (CheckIfRecordExists(player_record))
    {
        m_records.erase(std::find(m_records.begin(), m_records.end(), player_record));
// std::remove(m_records.begin(), m_records.end(), player_record);
        m_connection.ExecuteSQL("DELETE FROM player_records WHERE name='" + player_record.m_name + "'");
    }
}

void  DataBase_2048::Print() const
{
    for (auto &i : m_records)
    {
        LOG_INFO(i);
    }
}

bool  DataBase_2048::IsEmpty() const
{
    return m_records.empty();
}

void  DataBase_2048::UpdateRecords()
{
    FetchRecordsFromDataBase();
}

void  DataBase_2048::ClearDataBase()
{
    m_records.clear();
    m_connection.ExecuteSQL("DELETE FROM player_records");
}

void  DataBase_2048::FetchRecordsFromDataBase()
{
    auto  sql_result = m_connection.ExecuteSQL("SELECT * FROM player_records order by name");

    if (sql_result)
    {
        PlayerRecord  record;

        for (int i = 0; i < sql_result.GetRows(); ++i)
        {
            record.m_name  = sql_result.Get(i, 0);
            record.m_score = sql_result.Get(i, 1).toInt();

            if (auto found = std::find(m_records.begin(), m_records.end(), record); found == std::end(m_records))
            {
                m_records.push_back(record);
            }
        }
    }
}

bool  DataBase_2048::CheckIfRecordExists(const PlayerRecord &record) const
{
    if (record)
    {
        if (std::find(m_records.begin(), m_records.end(), record) != std::end(m_records))
        {
            return true;
        }

        return false;
    }

    return false;
}
