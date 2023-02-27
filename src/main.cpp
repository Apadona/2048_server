#include "gamewindow.hpp"
#include "gamelogic.hpp"

#include <QDebug>
#include <QApplication>

int  main(int argc, char *argv[])
{
  QApplication  app_2048(argc, argv);
  GameWindow    w;
  GameLogic     logic;

  // std::cout << "at first:\n:";
  std::cout << logic << std::endl;

  logic.Shift(ShiftDirection::NONE);
  std::cout << logic << std::endl;
  logic.Shift(ShiftDirection::LEFT);
  std::cout << logic << std::endl;
  logic.Shift(ShiftDirection::UP);
  std::cout << logic << std::endl;
  logic.Shift(ShiftDirection::DOWN);
  std::cout << logic << std::endl;
  logic.Shift(ShiftDirection::RIGHT);
  std::cout << logic << std::endl;

  w.show();

  // app_2048.processEvents();

  return app_2048.exec();
}
