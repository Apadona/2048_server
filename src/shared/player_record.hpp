#pragma once

#include <QString>
#include <QTime>
#include <QFile>
#include <QTextStream>
#include <QDataStream>

#include <iostream>
#include <optional>
#include <vector>

struct PlayerRecord
{
    PlayerRecord();

    PlayerRecord(QString name, quint32 score, const QTime &time = { });

    PlayerRecord(const char *serialized);

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

    quint32  m_score;
    QString  m_name;
    QTime    m_played_time;
};
using PlayerRecords = QVector<PlayerRecord>;

std::ostringstream& operator<<(std::ostringstream &out, const PlayerRecord &player_record);

QDataStream& operator<<(QDataStream &stream, const PlayerRecord &record);

//QDataStream& operator<<(QDataStream &stream, const PlayerRecords &record);

QDataStream& operator>>(QDataStream &stream, PlayerRecord &record);

//QDataStream& operator>>(QDataStream &stream, PlayerRecords &records);
