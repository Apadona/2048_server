#include "logger.hpp"

std::ostream  Logger::m_stdout(std::cout.rdbuf());
std::mutex    Logger::m_mutex;
bool          Logger::m_initialized(false);

bool  Logger::Init()
{
  // it only has to be initialized once.
  if (!IsInitialized())
  {
    try
    {
      m_stdout.copyfmt(std::cout);
      m_stdout.clear(std::cout.rdstate());
      m_stdout.basic_ios<char>::rdbuf(std::cout.rdbuf());
    }
    catch (...)
    {
      std::cerr << "cannot initialize logger....";

      return m_initialized; // which is false.
    }

    ;

    m_initialized = true;
  }

  return m_initialized;
}

bool  Logger::IsInitialized()
{
  return m_initialized;
}
