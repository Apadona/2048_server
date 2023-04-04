#include "client_layouts.hpp"
#include "client.hpp"
#include "csscolors.hpp"
#include <QDebug>

#include <QMouseEvent>

Client_2048_WidgetData::Client_2048_WidgetData(Client_2048 *app, Client_2048_Event assosiated_event):
    m_owner_app(app), m_assosiated_event(assosiated_event)
{
}

Client_2048_Button::Client_2048_Button():
    Client_2048_WidgetData(nullptr, Client_2048_Event::NONE)
{
    setObjectName("app_2048 Button");
    setText("dull");
}

Client_2048_Button::Client_2048_Button(Client_2048 *app, QString name, Client_2048_Event event):
    Client_2048_WidgetData(app, event)
{
    setObjectName("app_2048 Button");
    setText(name);
}

void  Client_2048_Button::mousePressEvent(QMouseEvent *e)
{
    if (m_owner_app)    // send the message only when there is an owner.
    {
        m_owner_app->HandleAppEvent(m_assosiated_event);
    }
}

Client_2048_TextEdit::Client_2048_TextEdit():
    Client_2048_WidgetData(nullptr, Client_2048_Event::NONE)
{
}

Client_2048_TextEdit::Client_2048_TextEdit(Client_2048 *app):
    Client_2048_WidgetData(app, Client_2048_Event::CHECK_INPUTTED_NAME)
{
}

void  Client_2048_TextEdit::keyPressEvent(QKeyEvent *event)
{
    QString  input_char = event->text();

    if (!input_char.isEmpty())
    {
        QString  written_text = toPlainText();

        if ((written_text.size() >= PlayerRegisteryLayout::MaxPlayerNameLength) && (event->key() != Qt::Key_Backspace))
        {
            return;
        }

        QTextEdit::keyPressEvent(event);

        m_owner_app->HandleAppEvent(Client_2048_Event::CHECK_INPUTTED_NAME);
    }
}

MainMenuLayout::MainMenuLayout(Client_2048 *app):
    m_owner_app(app),
    m_newgame_button(std::make_unique<Client_2048_Button>(m_owner_app, "New Game", Client_2048_Event::START_REGISTER_MENU)),
    m_scores_button(std::make_unique<Client_2048_Button>(m_owner_app, "Scores", Client_2048_Event::SHOW_SCORES)),
    m_exit_button(std::make_unique<Client_2048_Button>(m_owner_app, "Exit", Client_2048_Event::EXIT))
{
    setObjectName("MainMenuLayout");

    addWidget(m_newgame_button.get());

    addWidget(m_scores_button.get());

    addWidget(m_exit_button.get());
}

GameLayout::GameLayout(Client_2048 *app):
    m_owner_app(app),
    m_score(std::make_unique<QLabel>("0")),
    m_reset_button(std::make_unique<Client_2048_Button>(m_owner_app, "Reset", Client_2048_Event::RESET_GAME)),
    m_back_button(std::make_unique<Client_2048_Button>(m_owner_app, "back", Client_2048_Event::EXIT)),
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

ScoreBoardLayout::ScoreBoardLayout(Client_2048 *app):
    m_owner_app(app),
    m_back_button(std::make_unique<Client_2048_Button>(m_owner_app, "Exit", Client_2048_Event::EXIT)),
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
    if (!records.empty())
    {
        return;
    }

    for (auto &i : records)
    {
        int     index  = 1;
        QLabel *label1 = new QLabel(i.m_name);
        QLabel *label2 = new QLabel(QString::number(i.m_score));
        QLabel *label3 = new QLabel(i.m_played_time.toString());
        m_label_grid->addWidget(label1, index, 0);
        m_label_grid->addWidget(label2, index, 1);
        m_label_grid->addWidget(label3, index, 2);
        ++index;
    }
}

PlayerRegisteryLayout::PlayerRegisteryLayout(Client_2048 *app):
    m_owner_app(app),
    m_name_field(std::make_unique<Client_2048_TextEdit>(m_owner_app)),
    m_back_button(std::make_unique<Client_2048_Button>(m_owner_app, "back", Client_2048_Event::EXIT)),
    m_submit_button(std::make_unique<Client_2048_Button>(m_owner_app, "submit", Client_2048_Event::START_GAME)),
    m_info(std::make_unique<QLabel>("Please Enter your name.")),
    m_message(std::make_unique<QLabel>()),
    m_info_layout(std::make_unique<QHBoxLayout>()),
    m_message_layout(std::make_unique<QHBoxLayout>()),
    m_text_edit_layout(std::make_unique<QHBoxLayout>()),
    m_buttons_layout(std::make_unique<QHBoxLayout>())
{
    m_name_field->setFixedSize(150, 30);

    m_message->hide();
    m_message->setAlignment(Qt::AlignCenter);
    m_message->setAutoFillBackground(true);

    m_info->setAlignment(Qt::AlignCenter);
    m_info->setAutoFillBackground(true);

    m_info_layout->addWidget(m_info.get());
    m_message_layout->addWidget(m_message.get());
    m_text_edit_layout->addWidget(m_name_field.get());
    m_buttons_layout->addWidget(m_back_button.get());
    m_buttons_layout->addWidget(m_submit_button.get());

    addLayout(m_info_layout.get());
    addLayout(m_text_edit_layout.get());
    addLayout(m_buttons_layout.get());
    addLayout(m_message_layout.get());
}

void  PlayerRegisteryLayout::DisplayString(const QString &_string, bool error)
{
    if (!_string.isEmpty())
    {
        m_message->setText(_string);
        m_message->setAutoFillBackground(true);

        if (error)
        {
            m_message->setStyleSheet(_2048_CSSColors::GetErrorColor());
        }
        else
        {
            m_message->setStyleSheet(_2048_CSSColors::GetValidationColor());
        }

        m_message->show();
    }
}

void  PlayerRegisteryLayout::EmptyMessage()
{
    m_message->setText(QString::Null());
    m_message->hide();
}
