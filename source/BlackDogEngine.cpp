#include "BlackDogEngine.h"
#include "Debug/Logger.h"
#include <iostream>

namespace bde {

    RTTI_DEF(BlackDogEngine, "bde.Object.BlackDogEngine", Object);

    /* ****************************
    * Construction & Destruction *
    * ***************************/

    BlackDogEnginePtr BlackDogEngine::Create() {
        return Instance();
    }
    
    void BlackDogEngine::Destroy() {
        
    }

    BlackDogEngine::BlackDogEngine() {
    }

    BlackDogEngine::~BlackDogEngine() {
    }

    void BlackDogEngine::Update(const F64 &dT) {
        for (auto subsystem : mSubsystems){
            subsystem->Update(dT);
        }
    }

    /* ******************************
    * Initialization & Termination *
    * *****************************/
    void BlackDogEngine::Init() {
        initLoggers();
        LOG_INFO("Initializing Black Dog Engine");
        
        for(auto subsystem : mSubsystems){
            subsystem->Init();
        }
    }

    void BlackDogEngine::Terminate() {
        for (auto subsystem : mSubsystems){
            subsystem->Terminate();
        }
    }

    void BlackDogEngine::initLoggers() {
        Logger::SetLoggerForLevel(Logger::LoggerLevel::Debug,
                                  std::make_shared<Logger>(std::cout));
        Logger::SetLoggerForLevel(Logger::LoggerLevel::Info,
                                  std::make_shared<Logger>(std::cout));
        Logger::SetLoggerForLevel(Logger::LoggerLevel::Error,
                                  std::make_shared<Logger>(std::cout));
    }
    
    void BlackDogEngine::AddSubsystem(SubsystemPtr subsystem){
        mSubsystems.push_back(subsystem);
    }
}
