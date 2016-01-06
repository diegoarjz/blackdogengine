#ifndef LOGGER_H_
#define LOGGER_H_

#include <ostream>
#include <memory>

namespace bde {

#define LOG_DEBUG(MSG)  LOG(bde::Logger::LoggerLevel::Debug, MSG)
#define LOG_INFO(MSG)   LOG(bde::Logger::LoggerLevel::Info, MSG)
#define LOG_ERROR(MSG)  LOG(bde::Logger::LoggerLevel::Error, MSG)

#define LOG(LEVEL, MSG) bde::Logger::Log(LEVEL, MSG)

    class Logger;
    typedef std::shared_ptr<Logger> LoggerPtr;

    /**
    * Logging system.
	* 
	* The logging system has a static logging level, which can be set at runtime,
	* and affects which messages are logged.
	*
	* Statically holds different loggers for different log levels. Messages can be
	* logged globally throughout the rest of the code by the following:
	* 
	* Logger::Log(<log_level>, <log_message>);
	* 
	* where log_level is one of the defined in LoggerLevel:
	* 	* Debug
	*	* Info
	*	* Error
	*
	* Messages are only logged if they are of a higher priority than the logging level.
    */
    class Logger {
      public:
        /**
        * Enumerates the logging levels.
        */
        enum class LoggerLevel {
            Debug = 0,
            Info,
            Error,
            MAX_LOG_LEVELS
        };

      private:
		/// The different loggers globally available in the application.
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
		
		/* *******************
		* Static log methods *
		* *******************/
        static void Log(const LoggerLevel &level, const std::string &msg);
        static void SetLoggingLevel(const LoggerLevel &level);
        static LoggerLevel GetLoggingLevel();
        static void SetLoggerForLevel(const LoggerLevel &level, LoggerPtr l);

    }; // class Logger

} // namespace bde

#else

namespace bde {
    class Logger;
} // namespace bde
#endif
