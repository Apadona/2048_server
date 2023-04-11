#pragma once

#include <QDataStream>

#include <type_traits>
#include <cstring>

struct EmptyData
{
};

enum EmptyType
{
};

using PacketType = quint32;

class /*__attribute__((packed))*/ Packet
{
public:
    inline Packet()
    {
        ClearData();
    }

    inline Packet(const char *serialized_data, quint32 size)
    {
        QByteArray  array(serialized_data, size);

        *this = array;
    }

    Packet(const QByteArray &array)
    {
        *this = array;
    }

    template<typename Type,
             typename = typename std::enable_if<std::is_enum<Type>::value || std::is_integral<Type>::value>::type>
    Packet(const Type &type)
    {
        SetType(type);
    }

    Packet( const Packet& other )
    {
        m_type = other.m_type;
        m_raw_data = other.m_raw_data;
    }

    inline Packet& operator=( const char* data )
    {
        return *this << QByteArray(data);
    }


    inline Packet& operator=( const QByteArray& data )
    {
        return  *this << data;
    }

    inline quint32  Size() const
    {
        return m_raw_data.size();
    }

    void  ClearData()
    {
        m_type = 0;
        m_raw_data.clear();
    }

    template<typename Type = PacketType>
    inline void  SetType(Type type)
    {
        m_type = static_cast<PacketType>(type);

        m_raw_data.replace(0, 1, QString::number(m_type).toLatin1());
    }

    template<typename Type = PacketType>
    inline Type  GetType() const
    {
        return static_cast<Type>(m_type);
    }

    template<typename Data>
    inline Packet& operator<<(const Data &data)
    {
        QDataStream serializer(&m_raw_data,QIODevice::ReadWrite | QIODevice::Append);
//        serializer.setByteOrder(QDataStream::LittleEndian);

        auto  HandleSpecialCases = [&]()
        {

        };

        if constexpr (std::is_same<Data, const char *>::value)
        {
            if (data)
            {
                ClearData();
                m_raw_data += data;
                m_type = data.toInt();/*m_raw_data.mid(0, 3).toInt();*/

                return *this;
            }
        }

        if constexpr (std::is_same<Data, QByteArray>::value)
        {
            if (!data.isEmpty())
            {
                ClearData();
                m_raw_data += data;
                m_type = data.toInt();/*m_raw_data.mid(0, 3).toInt();*/

                return *this;
            }
        }

        serializer << data;

        return *this;
    }

    template<typename Data>
    inline const Packet& operator>>(Data &data)
    {
        QDataStream serializer(&m_raw_data,QIODevice::ReadWrite);
//        serializer.setByteOrder(QDataStream::LittleEndian);

        serializer.skipRawData(1);

        serializer >> data;

        return *this;
    }

    QByteArray  GetData() const
    {
        return m_raw_data;
    }

    inline const char* ToRawBytes()
    {
        return m_raw_data.data();
    }

    inline  operator const char *()
    {
        return ToRawBytes();
    }

    inline bool  IsEmpty() const
    {
        return Size() == 0;
    }

    inline  operator bool() const
    {
        return !IsEmpty();
    }

private:
    PacketType  m_type;
    QByteArray  m_raw_data;
};
