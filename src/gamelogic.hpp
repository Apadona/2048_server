#pragma once

#include <cstdint>

using sqaureValue = std::uint32_t;

enum class ShiftDirection
{
    LEFT,
    UP,
    DOWN,
    RIGHT
};

enum class GameStatus
{
    WIN,
    LOOSE,
    ONGOING
};

class GameLogic
{
public:
    GameLogic();

    GameLogic( const GameLogic& other ) = delete;
    GameLogic( GameLogic&& other ) = delete;

    GameLogic& operator=( const GameLogic& other ) = delete;
    GameLogic& operator=( GameLogic&& other ) = delete;

    void Shift( ShiftDirection direction );

    GameStatus GetStatus();

private:
    std::uint32_t m_values[16] = {0};
};
