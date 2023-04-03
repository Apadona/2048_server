#pragma once

#include <QString>
#include <QTime>
#include <QFile>
#include <QTextStream>

#include <iostream>
#include <optional>
#include <vector>

struct PlayerRecord
{
    PlayerRecord();

    PlayerRecord(QString name, quint32 score, const QTime &time = { });

    PlayerRecord(const PlayerRecord &other);

    PlayerRecord(PlayerRecord &&other);

    PlayerRecord& operator=(const PlayerRecord &other);

    PlayerRecord& operator=(PlayerRecord &&other);

    bool  operator<(const PlayerRecord &other) const;

    bool  operator==(const PlayerRecord &other) const;

    inline  operator bool() const
    {
        return !m_name.isEmpty();
    }

    inline bool  operator!() const
    {
        return !bool(*this);
    }

    QString  m_name;
    quint32  m_score;
    QTime    m_played_time;
};
std::ostringstream& operator<<(std::ostringstream &out, const PlayerRecord &player_record);

using PlayerRecords = std::vector<PlayerRecord>;
