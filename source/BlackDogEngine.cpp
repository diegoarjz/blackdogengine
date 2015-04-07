#include "BlackDogEngine.h"
#include "Logger.h"
#include <iostream>

namespace bde {

  RTTI_DEF(BlackDogEngine, "bde.Object.BlackDogEngine", Object);

  BlackDogEnginePtr BlackDogEngine::sInstance = nullptr;

  /* ****************************
  * Construction & Destruction *
  * ***************************/

  BlackDogEnginePtr BlackDogEngine::Create(){
    if(sInstance != nullptr){
      throw std::runtime_error("Black Dog Engine has already been created.");
    }

    sInstance = std::make_shared<BlackDogEngine>();

    return sInstance;
  }

  BlackDogEnginePtr BlackDogEngine::GetInstance(){
    return sInstance;
  }

  void BlackDogEngine::Destroy(){
    sInstance = nullptr;
  }

  BlackDogEngine::BlackDogEngine(){

  }

  BlackDogEngine::~BlackDogEngine(){

  }

  void BlackDogEngine::Update(const F64 &dT){

  }

  /* ******************************
  * Initialization & Termination *
  * *****************************/
  void BlackDogEngine::Init(){
    initLoggers();
    
  }

  void BlackDogEngine::Terminate(){

  }

  void BlackDogEngine::initLoggers(){
    Logger::SetLoggerForLevel(Logger::LoggerLevel::Debug, std::make_shared<Logger>(std::cout));
    Logger::SetLoggerForLevel(Logger::LoggerLevel::Info, std::make_shared<Logger>(std::cout));
    Logger::SetLoggerForLevel(Logger::LoggerLevel::Error, std::make_shared<Logger>(std::cout));
  }
}
