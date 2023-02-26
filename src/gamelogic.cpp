#include "gamelogic.hpp"

#include <QDebug>
#include <QRandomGenerator>

namespace
{
inline decltype(auto) GenerateRandomNumber()
{
  return QRandomGenerator::global()->generate();
}
}

GameLogic::Slot::Slot(SquareValue value, bool occupied):
  m_value(value), m_occupied(occupied)
{
}

GameLogic::Slot::Slot(const Slot &other)
{
  *this = other;
}

GameLogic::Slot& GameLogic::Slot::operator=(const Slot &other)
{
  if (this != &other)
  {
    m_value    = other.m_value;
    m_occupied = other.m_occupied;
  }

  return *this;
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
    break;

  case ShiftDirection::UP:
    break;

  case ShiftDirection::DOWN:
    break;

  case ShiftDirection::RIGHT:
    break;
  }

  Evaluate();
}

void  GameLogic::Evaluate()
{
}

GameStatus  GameLogic::GetStatus()
{
}

SquareIndex  GameLogic::ChooseRandomSlot() const
{
  SquareIndex  index;

  do
  {
    index = GenerateRandomNumber();
  } while (m_slots[index].IsOcupied());

  return index;
}
