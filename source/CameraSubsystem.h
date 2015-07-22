#ifndef __BlackDogEngine__CameraSubsystem__
#define __BlackDogEngine__CameraSubsystem__

#include <vector>

#include "Subsystem.h"
#include "Camera.h"

namespace bde {
    /**
     * Manages camera components.
     */
    class CameraSubsystem : public Subsystem{
    private:
        std::vector<CameraPtr> mComponents;
    public:
        /* ****************************
         * Construction & Destruction *
         * ***************************/
        CameraSubsystem();
        virtual ~CameraSubsystem();
        
        virtual void Init() override;
        virtual void Terminate() override;
        
        /**
         * Updates the transformation matrix of all components
         * that require update.
         */
        virtual void Update(const TIME_T &delta) override;
        
        CameraPtr CreateComponent();
        CameraPtr GetComponentForID(const U32 &componentId);
    }; // class TransformationSubsystem
}

#endif /* defined(__BlackDogEngine__CameraSubsystem__) */
