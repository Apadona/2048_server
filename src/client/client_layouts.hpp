#pragma once

#include <shared/player_record.hpp>
#include "gamelogic.hpp"
#include "client_events.hpp"

#include <QLayout>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QTextEdit>

#include <memory>
#include <array>

class Client_2048;

class Client_2048_WidgetData
{
public:
    Client_2048_WidgetData(Client_2048 *app, Client_2048_Event assosiated_event);

protected:
    Client_2048       *m_owner_app        = nullptr;
    Client_2048_Event  m_assosiated_event = Client_2048_Event::NONE;
};

class Client_2048_Button: public QPushButton, Client_2048_WidgetData
{
public:
    Client_2048_Button();

    Client_2048_Button(Client_2048 *app, QString name, Client_2048_Event event);

protected:
    virtual void  mousePressEvent(QMouseEvent *e) override;
};

class Client_2048_TextEdit: public QTextEdit, Client_2048_WidgetData
{
public:
    Client_2048_TextEdit();

    Client_2048_TextEdit(Client_2048 *app);

protected:
    virtual void  keyPressEvent(QKeyEvent *event) override;
};

class MainMenuLayout: public QVBoxLayout
{
    friend class Client_2048;

public:
    MainMenuLayout(Client_2048 *app);

private:
    Client_2048                         *m_owner_app;
    std::unique_ptr<Client_2048_Button>  m_newgame_button;
    std::unique_ptr<Client_2048_Button>  m_scores_button;
    std::unique_ptr<Client_2048_Button>  m_exit_button;
};

class GameLayout: public QVBoxLayout
{
    friend class Client_2048;

public:
    GameLayout(Client_2048 *app);

    void  DisplaySlotValues(const GameLogic::Slots &slot_values);

    void  Reset();

private:
    Client_2048                         *m_owner_app;
    QVector<QLabel *>                         m_slot_values;
    std::unique_ptr<QLabel>                   m_score;
    std::unique_ptr<Client_2048_Button>  m_reset_button;
    std::unique_ptr<Client_2048_Button>  m_back_button;
    std::unique_ptr<QHBoxLayout>              m_label_layout;
    std::unique_ptr<QGridLayout>              m_slot_grid;
    std::unique_ptr<QHBoxLayout>              m_button_layout;
};

class ScoreBoardLayout: public QVBoxLayout
{
    friend class Client_2048;

    struct PlayerDisplayInfo
    {
        std::unique_ptr<QLabel *>  m_score;
    };

public:
    ScoreBoardLayout(Client_2048 *app);

    void  DisplayScores(const PlayerRecords &records);

    void ClearLayouts();
private:
    void MakeLayout(const PlayerRecord& recood, quint32 row );
    QLabel* MakeLabel( const QString& title );
private:
    Client_2048                         *m_owner_app;
    QVector<QLabel *>                         m_labels;
    std::unique_ptr<Client_2048_Button>  m_back_button;
    std::unique_ptr<QHBoxLayout>              m_header_layout;
    std::unique_ptr<QGridLayout>              m_label_grid;
    std::unique_ptr<QHBoxLayout>              m_button_layout;
};

class PlayerRegisteryLayout: public QVBoxLayout
{
public:
    static constexpr quint32  MaxPlayerNameLength = 20;

    PlayerRegisteryLayout(Client_2048 *app);

    const QString  GetInputtedName() const
    {
        return m_name_field->toPlainText();
    }

    // displays an error for inputted name.
    void  DisplayString(const QString &_string, bool error);

    void  EmptyMessage();

private:
    Client_2048                           *m_owner_app;
    std::unique_ptr<Client_2048_TextEdit>  m_name_field;
    std::unique_ptr<Client_2048_Button>    m_back_button;
    std::unique_ptr<Client_2048_Button>    m_submit_button;
    std::unique_ptr<QLabel>                     m_info;
    std::unique_ptr<QLabel>                     m_message;
    std::unique_ptr<QHBoxLayout>                m_info_layout;
    std::unique_ptr<QHBoxLayout>                m_message_layout;
    std::unique_ptr<QHBoxLayout>                m_text_edit_layout;
    std::unique_ptr<QHBoxLayout>                m_buttons_layout;
};
