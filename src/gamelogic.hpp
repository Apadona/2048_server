#pragma once

#include <cstdint>

#include <QtGlobal>

using SquareValue = quint32;
using SquareIndex = quint32;

enum class ShiftDirection
{
  NONE,
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
  struct Slot
  {
public:
    Slot() = default;

    Slot(SquareValue value, bool occupied);

    Slot(const Slot &other);

    Slot& operator=(const Slot &other);

    // Deoccupy a place.
    void  DeOccupy();

    void  Occupy();

    bool  IsOcupied() const;

    SquareValue  m_value    = 0;
    bool         m_occupied = false;
  };

public:
  GameLogic() = default;

  GameLogic(const GameLogic &other) = delete;

  GameLogic(GameLogic &&other) = delete;

  GameLogic& operator=(const GameLogic &other) = delete;

  GameLogic& operator=(GameLogic &&other) = delete;

  void  Shift(ShiftDirection direction);

  void  Evaluate();

  GameStatus  GetStatus();

public:
  static constexpr SquareIndex  GameRows           = 4;
  static constexpr SquareIndex  GameColumns        = 4;
  static constexpr SquareValue  slot_default_value = 2;

private:
  SquareIndex  ChooseRandomSlot() const;

private:
  Slot  m_slots[GameRows * GameColumns];
};
