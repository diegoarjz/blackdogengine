#ifndef __BlackDogEngine__GOComponentHandle__
#define __BlackDogEngine__GOComponentHandle__

#include <stdio.h>
#include <memory>

#include "DataTypes.h"

namespace bde {
    
    class GOComponentHandleBase{
    public:
        virtual ~GOComponentHandleBase(){};
    };
    
    typedef std::shared_ptr<GOComponentHandleBase> GOComponentHandlePtr;
    
    /**
     * Provides an interface to access a component stored in a subsystem.
     */
    template<class SYSTEM_T, class COMPONENT_T>
    class GOComponentHandle : public GOComponentHandleBase{
    private:
        SYSTEM_T *mSubsystem;
        U32 mComponentID;
    public:
        GOComponentHandle(SYSTEM_T *system, const U32 &componentID){
            mSubsystem = system;
            mComponentID = componentID;
        }
        
        virtual ~GOComponentHandle(){
            
        }
        
        COMPONENT_T* GetComponent(){
            return mSubsystem->GetComponentForID(mComponentID);
        }
        
        // Remove, etc...
    }; // class GOComponentHandle
}

#endif /* defined(__BlackDogEngine__GOComponentHandle__) */
