#include "application.hpp"
#include "logger.hpp"

// #include <QApplication>

int  main(int argc, char *argv[])
{
  Logger::Init();

  Application_2048  app(argc, argv);

  return app.Start();
}
