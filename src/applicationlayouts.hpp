#pragma once

#include "playerscore.hpp"
#include "gamelogic.hpp"
#include "applicationevents.hpp"

#include <QLayout>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>

#include <memory>

class Application_2048;

class Application_2048_Button: public QPushButton
{
public:
  Application_2048_Button();

  Application_2048_Button(Application_2048 *app, QString name, Application_2048_Event event);

protected:
  virtual void  mousePressEvent(QMouseEvent *e) override;

protected:
  Application_2048       *m_owner_app;
  Application_2048_Event  m_assosiated_event;
};

class MainMenuLayout: public QVBoxLayout
{
  friend class Application_2048;

public:
  MainMenuLayout(Application_2048 *app);

private:
  Application_2048                         *m_owner_app;
  std::unique_ptr<Application_2048_Button>  m_newgame_button;
  std::unique_ptr<Application_2048_Button>  m_scores_button;
  std::unique_ptr<Application_2048_Button>  m_exit_button;
};

class GameLayout: public QGridLayout
{
  friend class Application_2048;

public:
  GameLayout(Application_2048 *app);

  void  DisplaySlotValues(const GameLogic::Slots &slot_values);

  void  Reset();

private:
  Application_2048             *m_owner_app;
  QVector<QLabel *>             m_slot_values;
  std::unique_ptr<QLabel>       m_score;
  std::unique_ptr<QPushButton>  m_reset_button;
};

class ScoreBoardLayout: public QHBoxLayout
{
  friend class Application_2048;

  struct PlayerDisplayInfo
  {
    std::unique_ptr<QLabel *>  m_score;
  };

public:
  ScoreBoardLayout(Application_2048 *app);

  void  DisplayScores(const PlayerRecords &records);

private:
  Application_2048             *m_owner_app;
  QVector<QLabel *>             m_score_labels;
  std::unique_ptr<QPushButton>  m_exit_button;
};
