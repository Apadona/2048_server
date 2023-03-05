#include "applicationlayouts.hpp"
#include "application.hpp"
#include "csscolors.hpp"
#include <QDebug>

#include <QMouseEvent>

Application_2048_Button::Application_2048_Button():
  m_owner_app(nullptr),
  m_assosiated_event(Application_2048_Event::NONE)
{
  setObjectName("app_2048 Button");
  setText("dull");
}

Application_2048_Button::Application_2048_Button(Application_2048 *app, QString name, Application_2048_Event event):
  m_owner_app(app), m_assosiated_event(event)
{
  setObjectName("app_2048 Button");
  setText(name);
}

void  Application_2048_Button::mousePressEvent(QMouseEvent *e)
{
  if (m_owner_app)    // send the message only when there is an owner.
  {
    m_owner_app->HandleAppEvent(m_assosiated_event);
  }
}

MainMenuLayout::MainMenuLayout(Application_2048 *app):
  m_owner_app(app),
  m_newgame_button(std::make_unique<Application_2048_Button>(m_owner_app, "New Game", Application_2048_Event::START_GAME)),
  m_scores_button(std::make_unique<Application_2048_Button>(m_owner_app, "Scores", Application_2048_Event::SHOW_SCORES)),
  m_exit_button(std::make_unique<Application_2048_Button>(m_owner_app, "Exit", Application_2048_Event::EXIT))
{
  setObjectName("MainMenuLayout");

  addWidget(m_newgame_button.get());

  addWidget(m_scores_button.get());

  addWidget(m_exit_button.get());
}

GameLayout::GameLayout(Application_2048 *app):
  m_owner_app(app),
  m_score(std::make_unique<QLabel>("0")),
  m_reset_button(std::make_unique<Application_2048_Button>(m_owner_app, "Reset", Application_2048_Event::RESET_GAME)),
  m_back_button(std::make_unique<Application_2048_Button>(m_owner_app, "back", Application_2048_Event::EXIT)),
  m_label_layout(std::make_unique<QHBoxLayout>()), m_slot_grid(std::make_unique<QGridLayout>()),
  m_button_layout(std::make_unique<QHBoxLayout>())
{
  setObjectName("GameLayout");

  for (int i = 0; i < GameLogic::game_rows; ++i)
  {
    for (int j = 0; j < GameLogic::game_columns; ++j)
    {
      QLabel *label = new QLabel("N/A");
      label->setAlignment(Qt::AlignCenter);
      label->setAutoFillBackground(true);
      m_slot_values.push_back(label);
      m_slot_grid->addWidget(m_slot_values[i * GameLogic::game_rows + j], i, j);
    }
  }

  m_button_layout->addWidget(m_reset_button.get());
  m_button_layout->addWidget(m_back_button.get());

  addLayout(m_slot_grid.get());
  addLayout(m_button_layout.get());
}

void  GameLayout::DisplaySlotValues(const GameLogic::Slots &slot_values)
{
  for (int i = 0; i < slot_values.size(); ++i)
  {
    m_slot_values[i]->setText(QString::number(slot_values[i].GetValue()));
    QString  color = _2048_CSSColors::GetBySlotValue(slot_values[i].GetValue());
    m_slot_values[i]->setStyleSheet(color);
  }
}

void  GameLayout::Reset()
{
  for (int i = 0; i < m_slot_values.size(); ++i)
  {
    m_slot_values[i]->setText("N/A");
  }
}

ScoreBoardLayout::ScoreBoardLayout(Application_2048 *app):
  m_owner_app(app),
  m_back_button(std::make_unique<Application_2048_Button>(m_owner_app, "Exit", Application_2048_Event::EXIT)),
  m_label_grid(std::make_unique<QGridLayout>()), m_button_layout(std::make_unique<QHBoxLayout>())
{
  setObjectName("ScoreBoardLayout");

  for (int i = 0; i < 3; ++i)
  {
    m_labels.push_back(new QLabel(m_label_headers[i]));
    m_labels.at(i)->setAlignment(Qt::AlignCenter);
    m_labels.at(i)->setAutoFillBackground(true);
    m_label_grid->addWidget(m_labels.at(i), 0, i);
  }

  m_button_layout->addWidget(m_back_button.get());

  addLayout(m_label_grid.get());
  addLayout(m_button_layout.get());
}

void  ScoreBoardLayout::DisplayScores(const PlayerRecords &records)
{
  // if( !records.empty() )
}
