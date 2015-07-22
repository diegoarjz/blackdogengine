#ifndef LOGGER_H_
#define LOGGER_H_

#include <ostream>
#include <memory>

namespace bde{

#define LOG_DEBUG(MSG)  LOG(bde::Logger::LoggerLevel::Debug, MSG)
#define LOG_INFO(MSG)   LOG(bde::Logger::LoggerLevel::Info, MSG)
#define LOG_ERROR(MSG)  LOG(bde::Logger::LoggerLevel::Error, MSG)

#define LOG(LEVEL, MSG) bde::Logger::Log(LEVEL, MSG)

  class Logger;
  typedef std::shared_ptr<Logger> LoggerPtr;

  /**
  * Implements a logging system.
  *
  * @author Diego Jesus <diego.a.r.jz@gmail.com>
  */
  class Logger{
  public:
    /**
    * Enumerates the logging levels.
    */
    enum class LoggerLevel{
      Debug = 0,
      Info,
      Error,
      MAX_LOG_LEVELS
    };

  private:
    static LoggerPtr    sLoggers[(int)LoggerLevel::MAX_LOG_LEVELS];
    static LoggerLevel  sLoggingLevel;

    std::ostream &mOutStream;
  public:

    /* ***************************
    * Construction & Destruction *
    * ***************************/
    Logger();
    Logger(std::ostream &outstream);
    Logger(Logger &other);
    ~Logger();

    /* ************
    * Log Methods *
    * ************/
    void Log(const std::string &msg);
    static void Log(const LoggerLevel &level, const std::string &msg);
    static void SetLoggingLevel(const LoggerLevel &level);
    static LoggerLevel GetLoggingLevel();
    static void SetLoggerForLevel(const LoggerLevel &level, LoggerPtr l);

  }; // class Logger

} // namespace bde

#else

namespace bde{
  class Logger;
} // namespace bde
#endif
