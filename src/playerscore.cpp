#include "playerscore.hpp"

PlayerRecord::PlayerRecord():
  m_name("Unknown"), m_score(0), m_play_time()
{
}

PlayerRecord::PlayerRecord(QString name, quint32 score, const QTime &time):
  m_name(name), m_score(score), m_play_time(time)
{
}

PlayerRecords  ReadPlayerRecords()
{
  QFile  file("player_scores.dat");

  if (file.exists())
  {
    file.open();
  }
}

void  WritePlayerRecords(const PlayerRecords &records)
{
}
