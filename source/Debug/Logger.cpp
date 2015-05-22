#include "Logger.h"
#include <iostream>

namespace bde{

  LoggerPtr           Logger::sLoggers[(int)Logger::LoggerLevel::MAX_LOG_LEVELS];
  Logger::LoggerLevel Logger::sLoggingLevel = LoggerLevel::Info;

  /* ***************************
  * Construction & Destruction *
  * ***************************/
  Logger::Logger():mOutStream(std::cout){

  }

  Logger::Logger(std::ostream &outstream):mOutStream(outstream){

  }

  Logger::Logger(Logger &other):mOutStream(other.mOutStream){

  }

  Logger::~Logger(){

  }

  /* ************
  * Log Methods *
  * ************/
  void Logger::Log(const std::string &msg){
    mOutStream << msg << std::endl;
  }

  void Logger::Log(const Logger::LoggerLevel &level, const std::string &msg){
    if(level >= sLoggingLevel){
      sLoggers[(int)level]->Log(msg);
    }
  }

  void Logger::SetLoggingLevel(const LoggerLevel &level){
    sLoggingLevel = level;
  }

  Logger::LoggerLevel Logger::GetLoggingLevel(){
    return sLoggingLevel;
  }

  void Logger::SetLoggerForLevel(const Logger::LoggerLevel &level, LoggerPtr l){
    sLoggers[(int)level] = l;
  }

} // namespace bde
