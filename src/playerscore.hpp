#pragma once

#include <QString>
#include <QTime>
#include <QFile>
#include <QTextStream>

struct PlayerRecord
{
    PlayerRecord();

    PlayerRecord( QString name, quint32 score, const QTime& time );

    QString m_name;
    quint32 m_score;
    QTime m_play_time;
};

using PlayerRecords = QVector<PlayerRecord>;

PlayerRecords ReadPlayerRecords();

void WritePlayerRecords( const PlayerRecords& player_records );
