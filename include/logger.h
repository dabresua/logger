/**
 * @file logger.h
 * @author Daniel Bretón (d.breton.suarez@gmail.com)
 * @brief Very basic logger inspired on GLogs
 * 
 *        Usage example
 *        @code {.cpp}
 *        LOG(logger::WARNING, send) << "Exception ocurred: " << e.what();
 *        @endcode
 * 
 *        The logger will append the log to a stringstream 
 *        At the end of the scope the destructor will call the user callback
 * @version 0.1
 * @date 2022-04-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#include <iostream>
#include <sstream>

namespace logger {
/**
 * @brief Prototype for user callback
 * 
 */
typedef void (*user_cb_t)(std::string str);

class Logger : public std::ostream {
private:
  std::stringstream ss;
  user_cb_t callback;

public:
  /**
   * @brief Construct a new Logger object
   * 
   * @param user_cb user callback
   */
  Logger(user_cb_t user_cb) : ss()
  {
    callback = user_cb;
  }

  /**
   * @brief Destroy the Logger object
   *        Calls the user function
   * 
   */
  ~Logger()
  {
    callback(ss.str());
  }

  /**
   * @brief returns the stringstream object
   * 
   * @return std::stringstream& 
   */
  std::stringstream &getSS()
  {
    return ss;
  }

  /**
   * @brief Returns the ostream
   *        It is imposible to stream something to an unnamed ostream
   *        This hack is required to avoid the problem
   * 
   * @return Logger& 
   */
  Logger &stream()
  {
    return *this;
  }
};

/**
 * @brief Overloaded operator
 * 
 * @tparam T the type must be supported by @ref std::stringstream
 * @param log logger object
 * @param val value to log
 * @return Logger& 
 */
template<class T>
inline Logger& operator<<(Logger &log, const T &val) { 
  log.getSS() << val;
  return log;
}

enum severity
{
  INFO = 0,
  WARNING = 1,
  ERROR = 2,
};

char get_severity(std::string str)
{
  if (str.size() > 0)
    return str[0];
  return INFO;
}

std::string get_message(std::string str)
{
  if (str.size() > 1)
    return str.substr(1);
  return "";
}

} /* logger */

/**
 * @brief logs a message
 * 
 * @param severity log severity
 * @param callback user callback
 */
#define LOG(severity, callback) logger::Logger(callback).stream() << severity
