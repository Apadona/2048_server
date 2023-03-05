#include "gamewindow.hpp"
#include "logger.hpp"

#include "application.hpp"

#include <QDebug>
#include <QKeyEvent>

ApplicationWindow::ApplicationWindow(QWidget *parent, Application_2048 *owner):
  QMainWindow(parent), m_owner_app(owner), m_stack_widget(std::make_unique<QStackedWidget>()),
  m_main_menu_screen(std::make_unique<QWidget>()), m_score_screen(std::make_unique<QWidget>()),
  m_game_screen(std::make_unique<QWidget>())
{
  // setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

  setFixedSize(200, 200);

  setObjectName("MainWindow");

  m_main_menu_screen->setObjectName("MainMenuWidget");
  m_score_screen->setObjectName("ScoresWidget");
  m_game_screen->setObjectName("GameWidget");

  m_stack_widget->addWidget(m_main_menu_screen.get());
  m_stack_widget->addWidget(m_score_screen.get());
  m_stack_widget->addWidget(m_game_screen.get());

  setCentralWidget(m_stack_widget.get());
}

void  ApplicationWindow::keyReleaseEvent(QKeyEvent *event)
{
  switch (event->key())
  {
  case Qt::Key_Left:
    m_owner_app->HandleAppEvent(Application_2048_Event::SHIFT_LEFT);
    break;
  case Qt::Key_Up:
    m_owner_app->HandleAppEvent(Application_2048_Event::SHIFT_UP);
    break;
  case Qt::Key_Right:
    m_owner_app->HandleAppEvent(Application_2048_Event::SHIFT_RIGHT);
    break;
  case Qt::Key_Down:
    m_owner_app->HandleAppEvent(Application_2048_Event::SHIFT_DOWN);
    break;
  case Qt::Key_Space:
    m_owner_app->HandleAppEvent(Application_2048_Event::UPDATE_SLOTS);
    break;
  case Qt::Key_Escape:
    m_owner_app->HandleAppEvent(Application_2048_Event::EXIT);
  }
}

void  ApplicationWindow::DisplayView(Application_2048_View view)
{
  PrepareStackWidget(view);
}

void  ApplicationWindow::PrepareStackWidget(Application_2048_View view)
{
  quint32  index, index_1, index_2;

  if (view == Application_2048_View::MAIN_MENU)
  {
    index = 0, index_1 = 1, index_2 = 2;
  }
  else if (view == Application_2048_View::SCORES)
  {
    index = 1, index_1 = 0, index_2 = 2;
  }
  else if (view == Application_2048_View::GAME)
  {
    index = 2, index_1 = 0, index_2 = 1;
  }
  else
  {
    LOG_CRITICAL("there are only 3 addressable indexes!");
  }

  m_stack_widget->widget(index_1)->hide();
  m_stack_widget->widget(index_2)->hide();
  m_stack_widget->widget(index)->show();
  m_stack_widget->setCurrentWidget(m_stack_widget->widget(index));
}
