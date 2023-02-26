#include "gamewindow.hpp"
#include "gamelogic.hpp"

#include <QDebug>
#include <QApplication>
#include <QPushButton>
#include <QGridLayout>
#include <QMessageBox>
#include <QVector>

int  main(int argc, char *argv[])
{
  QApplication  app_2048(argc, argv);
  GameWindow    w;

  w.setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

  w.setFixedSize(200, 200);
  QVector<QPushButton *>  button_list;

  for (int i = 0; i < GameLogic::GameRows *GameLogic::GameColumns; ++i)
  {
    QPushButton *button = new QPushButton();
    button_list.push_back(button);
  }

  QGridLayout *grid_layout = new QGridLayout();

  for (int i = 0; i < GameLogic::GameRows; ++i)
  {
    for (int j = 0; j < GameLogic::GameColumns; ++j)
    {
      grid_layout->addWidget(button_list[i * 4 + j], i, j);
    }
  }

  QWidget *widget = new QWidget();
  widget->setLayout(grid_layout);
  w.setCentralWidget(widget);

  w.show();

  // app_2048.processEvents();

  return app_2048.exec();
}
