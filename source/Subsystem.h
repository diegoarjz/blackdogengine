#ifndef __BlackDogEngine__Subsystem__
#define __BlackDogEngine__Subsystem__

#include "Object.h"
#include "DataTypes.h"

namespace bde {
    /**
     * Abstract class for an engine subsystem.
     */
    class Subsystem : public Object{
    private:
        
    public:
        RTTI_DECL;
        
        /* ****************************
         * Construction & Destruction *
         * ***************************/
        Subsystem();
        virtual ~Subsystem();
        
        virtual void Init() = 0;
        virtual void Terminate() = 0;
        
        virtual void Update(const TIME_T &delta) = 0;
        
    }; // class Subsystem

    typedef std::shared_ptr<Subsystem> SubsystemPtr;
} // namespace bde

#endif /* defined(__BlackDogEngine__Subsystem__) */
