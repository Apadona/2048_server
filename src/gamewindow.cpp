#include "gamewindow.hpp"
#include "eventhandler.hpp"

#include <QPushButton>
#include <QGridLayout>
#include <QDebug>

#include <string>

// GameWindow::GameWindow()
// {
// }

GameWindow::GameWindow(QWidget *parent):
  QMainWindow(parent), m_buttons(), m_layout(std::make_unique<QGridLayout>()),
  m_centeral_widget(std::make_unique<QWidget>())
{
  setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

  setFixedSize(200, 200);

  for (int i = 0; i < GameLogic::GameRows *GameLogic::GameColumns; ++i)
  {
    QPushButton *button = new QPushButton();
    m_buttons.push_back(button);
  }

  for (int i = 0; i < GameLogic::GameRows; ++i)
  {
    for (int j = 0; j < GameLogic::GameColumns; ++j)
    {
      m_layout->addWidget(m_buttons[i * 4 + j], i, j);
    }
  }

  m_centeral_widget->setLayout(m_layout.get());
  setCentralWidget(m_centeral_widget.get());
}

GameWindow::~GameWindow()
{
// delete m_layout;
// delete m_centeral_widget;
}

void  GameWindow::DrawGameSlots(const GameLogic::Slots &_slots)
{
  for (int i = 0; i < _slots.size(); ++i)
  {
    QString  str = QString::number(_slots[i].m_value);
    m_buttons[i]->setObjectName(str);
  }
}
