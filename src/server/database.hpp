#pragma once

#include "postgres_abstraction.hpp"
#include <shared/player_record.hpp>

#include <memory>

class DataBase_2048
{
public:
    DataBase_2048() = default;

    bool  Connect(const QString &user_name, const QString &database, const QString &user_password = { });

    DataBaseConnectionStatus  GetConnectionStatus() const;

    inline const PlayerRecords & GetRecords() const
    {
        return m_records;
    }

    void  SubmitRecord(const PlayerRecord &player_record);

    bool  IsEmpty() const;

    inline  operator bool() const
    {
        return m_connection.IsConnected();
    }

    inline bool  operator!() const
    {
        return !bool(*this);
    }

private:
    void  FetchRecordsFromDataBase();

private:
    PGConnectionWrapper  m_connection;
    PlayerRecords        m_records;
};
