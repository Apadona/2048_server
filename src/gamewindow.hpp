#pragma once

#include "gamelogic.hpp"

#include <QMainWindow>
#include <QVector>
#include <QPushButton>
#include <QGridLayout>

#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui
{
class GameWindow;
}
QT_END_NAMESPACE

class GameWindow: public QMainWindow
{
  Q_OBJECT

public:
  GameWindow(QWidget *parent = nullptr);

  ~GameWindow();

// public slots:
  void  DrawGameSlots(const GameLogic::Slots &_slots);

private:
  QVector<QPushButton *>        m_buttons;
  std::unique_ptr<QGridLayout>  m_layout;
  std::unique_ptr<QWidget>      m_centeral_widget;
};
