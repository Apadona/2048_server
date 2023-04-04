#include "gamewindow.hpp"
#include <utils/logger.hpp>

#include "client.hpp"

#include <QDebug>
#include <QKeyEvent>

ApplicationWindow::ApplicationWindow(QWidget *parent, Client_2048 *owner):
    QMainWindow(parent), m_owner_app(owner), m_stack_widget(std::make_unique<QStackedWidget>()),
    m_main_menu_screen(std::make_unique<QWidget>()), m_score_screen(std::make_unique<QWidget>()),
    m_game_screen(std::make_unique<QWidget>()), m_register_screen(std::make_unique<QWidget>())
{
    // setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    // setFixedSize(200, 200);

    setObjectName("MainWindow");

    m_main_menu_screen->setObjectName("MainMenuWidget");
    m_score_screen->setObjectName("ScoresWidget");
    m_game_screen->setObjectName("GameWidget");
    m_register_screen->setObjectName("RegisterScreen");

    m_stack_widget->addWidget(m_main_menu_screen.get());
    m_stack_widget->addWidget(m_score_screen.get());
    m_stack_widget->addWidget(m_game_screen.get());
    m_stack_widget->addWidget(m_register_screen.get());

    setCentralWidget(m_stack_widget.get());
}

void  ApplicationWindow::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Left:
        m_owner_app->HandleAppEvent(Client_2048_Event::SHIFT_LEFT);
        break;
    case Qt::Key_Up:
        m_owner_app->HandleAppEvent(Client_2048_Event::SHIFT_UP);
        break;
    case Qt::Key_Right:
        m_owner_app->HandleAppEvent(Client_2048_Event::SHIFT_RIGHT);
        break;
    case Qt::Key_Down:
        m_owner_app->HandleAppEvent(Client_2048_Event::SHIFT_DOWN);
        break;
    case Qt::Key_Escape:
        m_owner_app->HandleAppEvent(Client_2048_Event::EXIT);
    }
}

void  ApplicationWindow::AddLayout(QLayout *layout, Client_2048_View view)
{
    if (layout)
    {
        if (view == Client_2048_View::MAIN_MENU)
        {
            m_main_menu_screen->setLayout(layout);
        }
        else if (view == Client_2048_View::SCORES)
        {
            m_score_screen->setLayout(layout);
        }
        else if (view == Client_2048_View::GAME)
        {
            m_game_screen->setLayout(layout);
        }
        else if (view == Client_2048_View::REGISTER)
        {
            m_register_screen->setLayout(layout);
        }
    }
    else
    {
        LOG_WARNING("cannot set an empty layout for window!");
    }
}

void  ApplicationWindow::DisplayView(Client_2048_View view)
{
    PrepareStackWidget(view);
}

void  ApplicationWindow::PrepareStackWidget(Client_2048_View view)
{
    quint32  index, index_1, index_2, index_3;

    if (view == Client_2048_View::MAIN_MENU)
    {
        index = 0, index_1 = 1, index_2 = 2, index_3 = 3;
    }
    else if (view == Client_2048_View::SCORES)
    {
        index = 1, index_1 = 0, index_2 = 2, index_3 = 3;
    }
    else if (view == Client_2048_View::GAME)
    {
        index = 2, index_1 = 0, index_2 = 1, index_3 = 3;
    }
    else if (view == Client_2048_View::REGISTER)
    {
        index = 3, index_1 = 0, index_2 = 1, index_3 = 2;
    }
    else
    {
        LOG_CRITICAL("there are only 3 addressable indexes!");
    }

    m_stack_widget->widget(index)->show();
    m_stack_widget->widget(index_1)->hide();
    m_stack_widget->widget(index_2)->hide();
    m_stack_widget->widget(index_3)->hide();
    m_stack_widget->setCurrentWidget(m_stack_widget->widget(index));
}
