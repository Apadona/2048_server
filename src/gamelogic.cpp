#include "gamelogic.hpp"
#include "logger.hpp"

#include <QRandomGenerator>

namespace
{
inline quint32  GenerateRandomNumber()
{
  return QRandomGenerator::global()->generate();
}

inline quint32  URand(quint32 lower, quint32 upper)
{
  return lower + GenerateRandomNumber() % (upper + 1);
}
}

std::ostream& operator<<(std::ostream &log, const GameLogic &logic)
{
  for (int i = 0; i < logic.game_rows; ++i)
  {
    for (int j = 0; j < logic.game_columns; ++j)
    {
      auto &_slot = logic.m_slots[i * logic.game_rows + j];

      if (_slot.IsOcupied())
      {
        log << _slot.GetValue();
      }
      else
      {
        log << "N/A";
      }

      log << "  ";
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
  if (IsNot(other))
  {
    m_value    = other.m_value;
    m_occupied = other.m_occupied;
  }

  return *this;
}

GameLogic::Slot& GameLogic::Slot::operator+=(const GameLogic::Slot &other)
{
  m_value += other.m_value;

  return *this;
}

bool  GameLogic::Slot::operator==(const GameLogic::Slot &other) const
{
  return m_value == other.m_value;
}

bool  GameLogic::Slot::IsNot(const GameLogic::Slot &other) const
{
  return this != &other;
}

void  GameLogic::Slot::SetValue(SlotValue value)
{
  m_value    = value;
  m_occupied = true;
}

void  GameLogic::Slot::DeOccupy()
{
  m_value    = 0;
  m_occupied = false;
}

void  GameLogic::Slot::Occupy()
{
  m_value = (URand(0, 1)) ? GameLogic::slot_default_value_1 : GameLogic::slot_default_value_2;

  m_occupied = true;
}

bool  GameLogic::Slot::IsOcupied() const
{
  return m_occupied;
}

GameLogic::GameLogic()
{
  for (auto &i : m_slots)
  {
    i.DeOccupy();
  }
}

void  GameLogic::Start()
{
  m_score = 0;

  for (int i = 0; i < 2; ++i)
  {
    GenerateRandomSlot();
  }
}

void  GameLogic::ReStart()
{
  m_score = 0;

  SetAllSlots(0);
}

void  GameLogic::Shift(ShiftDirection direction)
{
  if (!CheckIfLost())
  {
    switch (direction)
    {
    case ShiftDirection::NONE:
      LOG_WARNING("shift direction cannot be NONE!\n");
      break;

    case ShiftDirection::LEFT:

      for (int i = 0; i < game_rows; ++i)
      {
        for (int j = 3; j > 0; --j)
        {
          auto &curr_slot = m_slots[i * game_rows + j];
          auto &next_slot = m_slots[i * game_rows + j - 1];

          EvaluateSlots(curr_slot, next_slot);
        }
      }

      break;

    case ShiftDirection::UP:

      for (int i = 3; i > 0; --i)
      {
        for (int j = 0; j < game_columns; ++j)
        {
          auto &curr_slot = m_slots[i * game_rows + j];
          auto &next_slot = m_slots[(i - 1) * game_rows + j];

          EvaluateSlots(curr_slot, next_slot);
        }
      }

      break;

    case ShiftDirection::DOWN:

      for (int i = 1; i < game_columns; ++i)
      {
        for (int j = 0; j < game_columns; ++j)
        {
          auto &curr_slot = m_slots[(i - 1) * game_rows + j];
          auto &next_slot = m_slots[i * game_rows + j];

          EvaluateSlots(curr_slot, next_slot);
        }
      }

      break;

    case ShiftDirection::RIGHT:

      for (int i = 0; i < game_rows; ++i)
      {
        for (int j = 1; j < game_columns; ++j)
        {
          auto &curr_slot = m_slots[i * game_rows + (j - 1)];
          auto &next_slot = m_slots[i * game_rows + j];

          EvaluateSlots(curr_slot, next_slot);
        }
      }

      break;
    }
  }

  Evaluate();
}

void  GameLogic::ReplaceSlots(Slot &first, Slot &second)
{
  second = first;
  first.DeOccupy();
}

SlotValue  GameLogic::MergeSlots(Slot &first, Slot &second)
{
  first += second;
  ReplaceSlots(first, second);

  return second.GetValue();
}

void  GameLogic::EvaluateSlots(Slot &first, Slot &second)
{
  if (first.IsOcupied())
  {
    if (second.IsOcupied())
    {
      if (first == second)
      {
        m_score += MergeSlots(first, second);
      }
    }
    else
    {
      ReplaceSlots(first, second);
    }
  }
}

bool  GameLogic::Evaluate()
{
  if (!CheckIfLost())
  {
    GenerateRandomSlot();

    return true;
  }

  return false;
}

bool  GameLogic::CheckIfLost() const
{
  return GetStatus() == GameStatus::LOOSE;
}

void  GameLogic::GenerateRandomSlot()
{
  auto  slot_index = ChooseRandomSlot();

  m_slots[slot_index].Occupy();
}

GameStatus  GameLogic::GetStatus() const
{
  // first check for win.
  for (const auto &i : m_slots)
  {
    if (i.GetValue() == GameLogic::win_condition_value)
    {
      return GameStatus::WIN;
    }
  }

  bool  loose = true;

  for (const auto &i : m_slots)
  {
    if (!i.IsOcupied())
    {
      loose = false;
    }
  }

  if (loose)
  {
    return GameStatus::LOOSE;
  }
  else
  {
    return GameStatus::ONGOING;
  }
}

SlotIndex  GameLogic::ChooseRandomSlot() const
{
  SlotIndex  index;

  do
  {
    index = URand(0, 15);
  } while (m_slots[index].IsOcupied());

  return index;
}

void  GameLogic::SetAllSlots(SlotValue value)
{
  if (value)
  {
    for (auto &i : m_slots)
    {
      i.SetValue(value);
    }
  }
  else // in case of 0 which is for reseting the game, just deoccupy.
  {
    for (auto &i : m_slots)
    {
      i.DeOccupy();
    }
  }
}
