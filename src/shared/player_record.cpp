#include "shared/player_record.hpp"
#include <utils/logger.hpp>

#include <QTextStream>

#include <cstring>

PlayerRecord::PlayerRecord():
    m_score(0), m_played_time(QTime::currentTime())
{
    m_name.clear();
}

PlayerRecord::PlayerRecord(QString name, quint32 score, const QTime &time):
    m_name(name), m_score(score), m_played_time(time)
{
}

PlayerRecord::PlayerRecord(const char *serialized)
{
    if (serialized)
    {
        std::memcpy(this, serialized, sizeof(*this));
    }
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

bool  PlayerRecord::operator<(const PlayerRecord &other) const
{
    return m_score < other.m_score;
}

bool  PlayerRecord::operator==(const PlayerRecord &other) const
{
    return m_name == other.m_name;
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

std::ostringstream& operator<<(std::ostringstream &out, const PlayerRecord &player_record)
{
    out << player_record.m_name.toStdString() << ' ' << player_record.m_score;

    return out;
}

QDataStream& operator<<(QDataStream &stream, const PlayerRecord &player_record)
{
    stream << player_record.m_name << player_record.m_score;

    return stream;
}

//QDataStream& operator<<(QDataStream &stream, const PlayerRecords &player_records)
//{
//    for (auto &i : player_records)
//    {
//        stream << i;
//    }

//    return stream;
//}

QDataStream& operator>>(QDataStream &stream, PlayerRecord &record)
{
    stream >> record.m_name >> record.m_score;

    return stream;
}

//QDataStream& operator>>(QDataStream &stream, PlayerRecords &records)
//{
//    PlayerRecord  record;

//    stream >> record;

//    records.push_back(std::move(record));

//    return stream;
//}
