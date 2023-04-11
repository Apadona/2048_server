#pragma once

#include "packet.hpp"

#include "player_record.hpp"

#include <array>

enum  PacketTypes
{
    INVALID = 1,                                   // invalid type which is set by default.
    REQUEST_RECORDS,                   // sent by client to server to recieve records from databse.
    RECIEVE_RECORDS,                   // sent by server to client to send the client the fetched records.
    SUBMIT_RECORD                   // sent by client to server to submit a record if it is not existent in database.
};

// using IncomingPacket       = Packet<std::array<char, 1024>, PacketTypes>;
// using RequestRecordsPacket = Packet<EmptyData, PacketTypes>;
// using RecieveRecordsPacket = Packet<PlayerRecords, PacketTypes>;
// using SubmitRecordPacket   = Packet<PlayerRecord, PacketTypes>;
