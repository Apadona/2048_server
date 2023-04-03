#pragma once

#include "postgres_abstraction.hpp"

#include <shared/player_record.hpp>
#include <utils/logger.hpp>

#include <memory>

class DataBase_2048
{
public:
    DataBase_2048() = default;

    DataBase_2048(const QString &user_name, const QString &database, const QString &user_passwor = { });

    bool  Connect(const QString &user_name, const QString &database, const QString &user_password = { });

    DataBaseConnectionStatus  GetConnectionStatus() const;

    inline const PlayerRecords & GetRecords() const
    {
        return m_records;
    }

    bool  SubmitRecord(const PlayerRecord &player_record);

    void  RemoveRecord(const PlayerRecord &player_record);

    void  Print() const;

    void  UpdateRecords();

    void  ClearDataBase();

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

    bool  CheckIfRecordExists(const PlayerRecord &record) const;

private:
    QString              m_user_name;
    QString              m_user_password;
    QString              m_database_name;
    PGConnectionWrapper  m_connection;
    PlayerRecords        m_records;
};
