#ifndef BLACKDOGENGINE_H_
#define BLACKDOGENGINE_H_

#include <map>
#include <vector>
#include <list>

#include "DataTypes.h"
#include "Object.h"
#include "Singleton.h"
#include "Subsystem.h"

namespace bde {
    
    class BlackDogEngine;
    typedef std::shared_ptr<BlackDogEngine> BlackDogEnginePtr;
    
    /**
     * Main Black Dog Engine class.
     * Owns all subsystems composing a game and subclasses a messaging system
     * that allows inter-system communication.
     *
     * It is responsible for disposing of all subsystems.
     * There can only be one BlackDogEngine instance in an application, as such it is
     * a singleton.
     */
    class BlackDogEngine : public Object, public Singleton<BlackDogEngine> {
    private:
        /// List of all subsystems
        std::list<SubsystemPtr> mSubsystems;
    public:
        RTTI_DECL
        
        /* ****************************
         * Construction & Destruction *
         * ***************************/
        static BlackDogEnginePtr Create();
        static void              Destroy();
        
        BlackDogEngine();
        virtual ~BlackDogEngine();
        
        /**
         * Updates all subsystems in order.
         * @param dT [in] The elapsed time in seconds.
         */
        void Update(const TIME_T &dT);
        
        /* ******************************
         * Initialization & Termination *
         * *****************************/
        void Init();
        void Terminate();
        
        void AddSubsystem(SubsystemPtr subsystem);
    private:
        
        void initLoggers();
    }; // class BlackDogEngine
    
} // namespace bde

#else
namespace bde {
    class BlackDogEngine;
} // namespace bde
#endif
