#include "playerscore.hpp"
#include <utils/logger.hpp>

#include <QTextStream>

PlayerRecord::PlayerRecord():
    m_name("Unknown"), m_score(0), m_played_time(QTime::currentTime())
{
}

PlayerRecord::PlayerRecord(QString name, quint32 score, const QTime &time):
    m_name(name), m_score(score), m_played_time(time)
{
}

PlayerRecord::PlayerRecord(const PlayerRecord &other)
{
    *this = other;
}

PlayerRecord::PlayerRecord(PlayerRecord &&other)
{
    *this = std::forward<PlayerRecord>(other);
}

PlayerRecord& PlayerRecord::operator=(const PlayerRecord &other)
{
    if (this != &other)
    {
        m_name        = other.m_name;
        m_score       = other.m_score;
        m_played_time = other.m_played_time;
    }

    return *this;
}

PlayerRecord& PlayerRecord::operator=(PlayerRecord &&other)
{
    if (this != &other)
    {
        m_name        = std::move(other.m_name);
        m_score       = other.m_score;
        m_played_time = std::move(other.m_played_time);

        other.m_score = 0;
        // Qt says it is deprecated.
// other.m_played_time.restart();
    }

    return *this;
}

std::optional<PlayerRecords>  ReadPlayerRecords()
{
    QFile  file("player_scores.dat");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        LOG_FATAL("error! cannot open player_scores.dat file for reading!");

        return std::nullopt;
    }

    QTextStream    reader(&file);
    QString        read_data;
    PlayerRecords  records;
    read_data = reader.readLine();

    while (!read_data.isNull())
    {
        PlayerRecord  temp;
        reader >> temp.m_name;
        reader >> temp.m_score;

        records.push_back(std::move(temp));

        read_data = reader.readLine();
    }

    file.close();

    if (records.empty())
    {
        return std::nullopt;
    }

    return std::move(records);
}

void  WritePlayerRecords(const PlayerRecords &records)
{
    if (records.empty())
    {
        LOG_INFO("records sent to be written to file are empty!");

        return;
    }

    QFile  file("player_scores.dat");

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        LOG_FATAL("error! cannot open player_scores.dat file for writing!");

        return;
    }

    QTextStream  writer(&file);

    for (auto &i : records)
    {
        writer << i.m_name << ' ' << i.m_score << '\n';
    }
}
