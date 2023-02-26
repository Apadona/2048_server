#include "gamewindow.hpp"

#include <QApplication>
#include <QDebug>
#include <QPushButton>
#include <QGridLayout>
#include <QMessageBox>
#include <QVector>

int  main(int argc, char *argv[])
{
  QApplication  app_2048(argc, argv);
  GameWindow    w;

  w.resize(100, 50);

  QVector<QPushButton *>  button_list;

  for (int i = 0; i < 16; ++i)
  {
    QPushButton *button = new QPushButton();
    // button->resize(100, 100);
    button_list.push_back(button);
  }

  QGridLayout *grid_layout = new QGridLayout();

  for (int i = 0; i < 4; ++i)
  {
    for (int j = 0; j < 4; ++j)
    {
      grid_layout->addWidget(button_list[i * 4 + j], i, j);
    }
  }

  QWidget *widget = new QWidget();
  widget->setLayout(grid_layout);
  w.setCentralWidget(widget);

  w.show();

  app_2048.processEvents();

  return app_2048.exec();
}
