#pragma once

#include "qobject.h"
#include "qobjectdefs.h"
#include <cstdint>

#include <QEvent>
#include <QDebug>
#include <QtGlobal>

#include <iostream> // for debug test. temporary.
#include <array>

using SlotValue = quint32;
using SlotIndex = quint32;
using GameScore = quint32;

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
  WIN     = 1,         // when one slot reaches the value 2048. but game continiues.
  LOOSE   = 2,         // when all the slots are occupied and no valid move can be made.
  ONGOING = 3        // when neather of the above conditions are met.
};

class GameLogic
{
public:
  class Slot
  {
public:
    Slot();

    Slot(SlotValue value, bool occupied);

    Slot(const Slot &other);

    Slot& operator=(const Slot &other);

    Slot& operator+=(const Slot &other);

    bool  operator==(const Slot &other) const;

    // just for safety measures. checks whether the slots are not the same.
    bool  IsNot(const Slot &other) const;

    // temporary
    void  SetValue(SlotValue value);

    inline SlotValue  GetValue() const
    {
      return m_value;
    }

    // Deoccupy a place.
    void  DeOccupy();

    void  Occupy();

    bool  IsOcupied() const;

private:
    SlotValue  m_value;
    bool       m_occupied;
  };

  static constexpr SlotIndex  game_rows            = 4;
  static constexpr SlotIndex  game_columns         = 4;
  static constexpr SlotValue  slot_default_value_1 = 2;
  static constexpr SlotValue  slot_default_value_2 = 4;
  static constexpr SlotValue  win_condition_value  = 2048;

  using Slots = std::array<Slot, game_rows *game_columns>;

  friend std::ostream& operator<<(std::ostream &log, const GameLogic &logic);

public:
  GameLogic();

  GameLogic(const GameLogic &other) = delete;

  GameLogic(GameLogic &&other) = delete;

  GameLogic& operator=(const GameLogic &other) = delete;

  GameLogic& operator=(GameLogic &&other) = delete;

  void  Start(); // starts the game by occuping two slots.

  void  ReStart(); // restarts the game.

  void  Shift(ShiftDirection direction);

  void  CheckForColision();

  bool  Evaluate();

  void  GenerateRandomSlot();

  GameStatus  GetStatus();

  static inline constexpr SlotIndex  GetGameSize()
  {
    return game_rows * game_columns;
  }

  inline const Slots & GetSlots() const
  {
    return m_slots;
  }

  inline GameScore  GetGameScore() const
  {
    return m_score;
  }

private:
  void  OccupySlot(SlotIndex index);

// merges first slot into second slot.
  void  MergeSlots(Slot &first, Slot &second);

  SlotIndex  ChooseRandomSlot() const;

  void  SetAllSlots(SlotValue value);

private:
  Slots      m_slots;
  GameScore  m_score;
};
