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

class GameLogic: public QObject
{
  Q_OBJECT

public:
  struct Slot
  {
public:
    Slot();

    Slot(SlotValue value, bool occupied);

    Slot(const Slot &other);

    Slot& operator=(const Slot &other);

    Slot& operator+=(const Slot &other);

    // temporary
    void  Set(SlotValue value);

    // Deoccupy a place.
    void  DeOccupy();

    void  Occupy();

    bool  IsOcupied() const;


    SlotValue  m_value;
    bool       m_occupied;
  };
  static constexpr SlotIndex  GameRows           = 4;
  static constexpr SlotIndex  GameColumns        = 4;
  static constexpr SlotValue  slot_default_value = 2;

  using Slots = std::array<Slot, GameRows *GameColumns>;

  // for debugging purposes.
  friend QDebug& operator<<(QDebug &log, const GameLogic &logic);

  // temporary.
  friend std::ostream& operator<<(std::ostream &log, const GameLogic &logic);

public:
  GameLogic() = default;

  GameLogic(const GameLogic &other) = delete;

  GameLogic(GameLogic &&other) = delete;

  GameLogic& operator=(const GameLogic &other) = delete;

  GameLogic& operator=(GameLogic &&other) = delete;

  void  Shift(ShiftDirection direction);

  void  Evaluate();

  GameStatus  GetStatus();

  static inline constexpr SlotIndex  GetGameSize()
  {
    return GameRows * GameColumns;
  }

  inline const Slots & GetSlots() const
  {
    return m_slots;
  }

public slots:
  void  HandleEventFromWindow(QEvent event);

  // using Slots = std::array<Slot, GameLogic::GetGameSize()>;

private:
  SlotIndex  ChooseRandomSlot() const;

  void  SetAllSlots(SlotValue value);

private:
  Slots  m_slots;
};
