#pragma once

#include "playerscore.hpp"
#include "gamelogic.hpp"
#include "applicationevents.hpp"

#include <QLayout>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QTextEdit>

#include <memory>
#include <array>

class Application_2048;

class Application_2048_WidgetData
{
public:
  Application_2048_WidgetData(Application_2048 *app, Application_2048_Event assosiated_event);

protected:
  Application_2048       *m_owner_app        = nullptr;
  Application_2048_Event  m_assosiated_event = Application_2048_Event::NONE;
};

class Application_2048_Button: public QPushButton, Application_2048_WidgetData
{
public:
  Application_2048_Button();

  Application_2048_Button(Application_2048 *app, QString name, Application_2048_Event event);

protected:
  virtual void  mousePressEvent(QMouseEvent *e) override;
};

class Application_2048_TextEdit: public QTextEdit, Application_2048_WidgetData
{
public:
  Application_2048_TextEdit();

  Application_2048_TextEdit(Application_2048 *app);

protected:
  virtual void  keyPressEvent(QKeyEvent *event) override;
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

class GameLayout: public QVBoxLayout
{
  friend class Application_2048;

public:
  GameLayout(Application_2048 *app);

  void  DisplaySlotValues(const GameLogic::Slots &slot_values);

  void  Reset();

private:
  Application_2048                         *m_owner_app;
  QVector<QLabel *>                         m_slot_values;
  std::unique_ptr<QLabel>                   m_score;
  std::unique_ptr<Application_2048_Button>  m_reset_button;
  std::unique_ptr<Application_2048_Button>  m_back_button;
  std::unique_ptr<QHBoxLayout>              m_label_layout;
  std::unique_ptr<QGridLayout>              m_slot_grid;
  std::unique_ptr<QHBoxLayout>              m_button_layout;
};

class ScoreBoardLayout: public QVBoxLayout
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
  Application_2048                         *m_owner_app;
  std::array<QString, 3>                    m_label_headers = { "PlayerName:", "PlayerScore:", "PlayedTime:" };
  QVector<QLabel *>                         m_labels;
  std::unique_ptr<Application_2048_Button>  m_back_button;
  std::unique_ptr<QGridLayout>              m_label_grid;
  std::unique_ptr<QHBoxLayout>              m_button_layout;
};

class PlayerRegisteryLayout: public QVBoxLayout
{
public:
  static constexpr quint32  MaxPlayerNameLength = 20;

  PlayerRegisteryLayout(Application_2048 *app);

  const QString  GetInputtedName() const
  {
    return m_name_field->toPlainText();
  }

  // displays an error for inputted name.
  void  DisplayString(const QString &_string, bool error);

  void  EmptyMessage();

private:
  Application_2048                           *m_owner_app;
  std::unique_ptr<Application_2048_TextEdit>  m_name_field;
  std::unique_ptr<Application_2048_Button>    m_back_button;
  std::unique_ptr<Application_2048_Button>    m_submit_button;
  std::unique_ptr<QLabel>                     m_info;
  std::unique_ptr<QLabel>                     m_message;
  std::unique_ptr<QHBoxLayout>                m_info_layout;
  std::unique_ptr<QHBoxLayout>                m_message_layout;
  std::unique_ptr<QHBoxLayout>                m_text_edit_layout;
  std::unique_ptr<QHBoxLayout>                m_buttons_layout;
};
