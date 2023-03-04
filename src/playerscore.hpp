#pragma once

#include <QString>
#include <QTime>
#include <QFile>
#include <QTextStream>

#include <optional>
#include <vector>

struct PlayerRecord
{
  PlayerRecord();

  PlayerRecord(QString name, quint32 score, const QTime &time);

  PlayerRecord(const PlayerRecord &other);

  PlayerRecord(PlayerRecord &&other);

  PlayerRecord& operator=(const PlayerRecord &other);

  PlayerRecord& operator=(PlayerRecord &&other);

  QString  m_name;
  quint32  m_score;
};

using PlayerRecords = std::vector<PlayerRecord>;

std::optional<PlayerRecords>  ReadPlayerRecords();

void  WritePlayerRecords(const PlayerRecords &player_records);
