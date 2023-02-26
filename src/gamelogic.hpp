#pragma once

#include <cstdint>

using SquareValue = std::uint32_t;
using SquareIndex = std::uint32_t;

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
  static constexpr SquareValue  slot_default_value = 2;
  struct Slot
  {
public:
    Slot() = default;

    Slot(SquareValue value, bool occupied);

    Slot(const Slot &other);

    Slot& operator=(const Slot &other);

    // Deoccupy a place.
    void  Deoccupy();

    SquareValue  m_value;
    bool         m_occupied;
  };

public:
  GameLogic() = default;

  GameLogic(const GameLogic &other) = delete;

  GameLogic(GameLogic &&other) = delete;

  GameLogic& operator=(const GameLogic &other) = delete;

  GameLogic& operator=(GameLogic &&other) = delete;

  void  Shift(ShiftDirection direction);

  GameStatus  GetStatus();

private:
  void  GenerateSlot();

  SquareIndex  ChooseRandomSlot() const;

private:
  Slot  m_slots[16];
};
