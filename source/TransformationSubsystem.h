#ifndef __BlackDogEngine__TransformationSubsystem__
#define __BlackDogEngine__TransformationSubsystem__

#include <stdio.h>
#include <vector>

#include "Subsystem.h"
#include "TransformComponent.h"
#include "GOComponentHandle.h"

namespace bde{
    /**
     * Manages transformation components.
     */
    class TransformationSubsystem : public Subsystem{
    private:
        std::vector<TransformComponentPtr> mComponents;
    public:
        /* ****************************
         * Construction & Destruction *
         * ***************************/
        TransformationSubsystem();
        virtual ~TransformationSubsystem();
        
        virtual void Init() override;
        virtual void Terminate() override;
        
        /**
         * Updates the transformation matrix of all components
         * that require update.
         */
        virtual void Update(const TIME_T &delta) override;
        
        TransformComponentPtr CreateComponent();
        
        TransformComponentPtr GetComponentForID(const U32 &componentId);
    }; // class TransformationSubsystem
} // namespace bde

#else
namespace bde{
    class TransformationSubsystem;
} // namespace bde
#endif /* defined(__BlackDogEngine__TransformationSubsystem__) */
