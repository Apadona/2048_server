#pragma once

#include "gamelogic.hpp"

#include <QMainWindow>
#include <QVector>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QStackedWidget>
#include <QDialog>

#include <memory>

enum class Client_2048_View
{
  MAIN_MENU,
  REGISTER,
  SCORES,
  GAME
};

class Client_2048;
class ApplicationWindow: public QMainWindow
{
  Q_OBJECT

  friend class Client_2048;

public:
  ApplicationWindow(QWidget          *parent  = nullptr,
                    Client_2048 *m_owner = nullptr);

  void  AddLayout(QLayout *layouts, Client_2048_View view);

private:
  void  DisplayView(Client_2048_View view);

  void  PrepareStackWidget(Client_2048_View index);

private:
  Client_2048                *m_owner_app;
  std::unique_ptr<QStackedWidget>  m_stack_widget;
  std::unique_ptr<QWidget>         m_main_menu_screen;
  std::unique_ptr<QWidget>         m_register_screen;
  std::unique_ptr<QWidget>         m_score_screen;
  std::unique_ptr<QWidget>         m_game_screen;

protected:
  virtual void  keyReleaseEvent(QKeyEvent *event) override;
};
