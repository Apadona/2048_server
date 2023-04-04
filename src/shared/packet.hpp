#pragma once

#include <type_traits>

struct EmptyData
{
};

enum EmptyType
{
};

template<typename Data = EmptyData, typename Type = EmptyType, typename = typename std::enable_if<std::is_enum<Type>::value>::type>
class Packet
{
public:
    Packet() = default;

    Packet(const Packet<Data, Type> &other)
    {
        *this = other;
    }

    Packet(const Data &data, Type type)
    {
        SetData(data);
        SetType(type);
    }

    inline Packet<Data, Type>& operator=(const Packet<Data, Type> &other)
    {
        if (this != &other)
        {
            m_data = other.m_data;
            m_type = other.m_type;
        }

        return *this;
    }

    inline bool  operator==(const Packet<Data, Type> &other)
    {
        return m_type == other.m_type && m_data == other.m_data;
    }

    void  SetData(const Data &data)
    {
        m_data = data;
    }

    void  SetType(Type type)
    {
        m_type = type;
    }

    const Data & GetData() const
    {
        return m_data;
    }

    Type  GetType() const
    {
        return m_type;
    }

    inline const char* ToRawBytes() const
    {
        return reinterpret_cast<const char *>(&m_data);
    }

    inline  operator const char *() const
    {
        return ToRawBytes();
    }

private:
    Data  m_data;
    Type  m_type;
};
