#pragma once

#include <iostream>

#include <sstream>
#include <mutex>

namespace
{
template<typename T>
inline std::string  AppendStrings(T &&value)
{
  std::ostringstream  oss;

  oss << value;

  return oss.str();
}

template<typename T, typename ... Args>
inline std::string  AppendStrings(T &&value, Args && ... args)
{
  return AppendStrings(std::forward<T>(value)) + AppendStrings(std::forward<Args>(args)...);
}
}

// the hell with the freaking QT!!! hail std C++!
// simple singleton pattern that provides enough encapsulation.
class Logger
{
public:
  static bool  Init();

  static bool  IsInitialized();

  inline static std::ostream & Get()
  {
    return m_stdout;
  }

  // thread safe logging.
  template<typename First, typename ... Args>
  static void  Log(First &&first, Args && ... args)
  {
    std::scoped_lock<std::mutex>  lock(m_mutex);
    std::string                   message;

    message += AppendStrings(std::forward<First>(first), std::forward<Args>(args)...);

    if (message.empty())
    {
      return;
    }

    m_stdout << message << std::endl;
  }

private:
  static std::mutex    m_mutex;
  static std::ostream  m_stdout;
  static bool          m_initialized;
};

#define LOG_SOURCE() \
  Logger::Log(__FILE__, __LINE__, __FUNCTION__)

#define LOG_ASSERT(condition, message) \
  if (!condition)                      \
  LOG_FATAL (message)

#define LOG_INFO(...) \
  Logger::Log("info:\n", __VA_ARGS__)

#define LOG_CRITICAL(...) \
  Logger::Log("critical:\n", __VA_ARGS__)

#define LOG_WARNING(...) \
  Logger::Log("warning:\n", __VA_ARGS__)

#define LOG_FATAL(...) \
  Logger::Log("fatal:\n", __VA_ARGS__)

#define LOG_DEBUG(...) \
  Logger::Log("debug:\n", __VA_ARGS__)
