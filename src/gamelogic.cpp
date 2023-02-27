#include "gamelogic.hpp"

#include <QRandomGenerator>

namespace
{
inline decltype(auto) GenerateRandomNumber()
{
  return QRandomGenerator::global()->generate();
}
}

QDebug& operator<<(QDebug &log, const GameLogic &logic)
{
  for (int i = 0; i < logic.GameRows; ++i)
  {
    for (int j = 0; j < logic.GameColumns; ++j)
    {
      log << ((logic.m_slots[i].m_occupied) ? logic.m_slots[i].m_value : 'o') << ' ';
    }

    log << '\n';
  }

  return log;
}

std::ostream& operator<<(std::ostream &log, const GameLogic &logic)
{
  for (int i = 0; i < logic.GameRows; ++i)
  {
    for (int j = 0; j < logic.GameColumns; ++j)
    {
      log << ((logic.m_slots[i].m_occupied) ? logic.m_slots[i].m_value : 'o') << ' ';
    }

    log << '\n';
  }

  return log;
}

GameLogic::Slot::Slot():
  m_value(0), m_occupied(false)
{
}

GameLogic::Slot::Slot(SlotValue value, bool occupied):
  m_value(value), m_occupied(occupied)
{
}

GameLogic::Slot::Slot(const Slot &other)
{
  *this = other;
}

GameLogic::Slot& GameLogic::Slot::operator=(const GameLogic::Slot &other)
{
  if (this != &other)
  {
    m_value    = other.m_value;
    m_occupied = other.m_occupied;
  }

  return *this;
}

// GameLogic::Slot& GameLogic::Slot::operator+(const GameLogic::Slot &other) const
// {
// return Slot(m_value + other.m_value, m_occupied);
// }

GameLogic::Slot& GameLogic::Slot::operator+=(const GameLogic::Slot &other)
{
  m_value += other.m_value;

  return *this;
}

void  GameLogic::Slot::Set(SlotValue value)
{
  m_value = value;
}

void  GameLogic::Slot::DeOccupy()
{
  m_value    = 0;
  m_occupied = false;
}

void  GameLogic::Slot::Occupy()
{
  m_value    = GameLogic::slot_default_value;
  m_occupied = true;
}

bool  GameLogic::Slot::IsOcupied() const
{
  return m_occupied;
}

void  GameLogic::Shift(ShiftDirection direction)
{
  switch (direction)
  {
  case ShiftDirection::NONE:
    qWarning() << "shift direction cannot be NONE!\n";
    break;

  case ShiftDirection::LEFT:
    SetAllSlots(1);
    break;

  case ShiftDirection::UP:
    SetAllSlots(2);
    break;

  case ShiftDirection::DOWN:
    SetAllSlots(3);
    break;

  case ShiftDirection::RIGHT:
    SetAllSlots(4);
    break;
  }

  // Evaluate();
}

void  GameLogic::Evaluate()
{
}

GameStatus  GameLogic::GetStatus()
{
  // for now just to avoid compiler warning.
  return GameStatus::ONGOING;
}

void  GameLogic::HandleEventFromWindow(QEvent event)
{
}

SlotIndex  GameLogic::ChooseRandomSlot() const
{
  SlotIndex  index;

  do
  {
    index = GenerateRandomNumber();
  } while (m_slots[index].IsOcupied());

  return index;
}

void  GameLogic::SetAllSlots(SlotValue value)
{
  for (auto &i : m_slots)
  {
    i.Set(value);
  }
}
