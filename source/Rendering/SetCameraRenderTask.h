#ifndef __BlackDogEngine__SetCameraRenderTask__
#define __BlackDogEngine__SetCameraRenderTask__

#include "RenderTask.h"
#include "../Camera.h"

namespace bde {
    
    /**
     * Render task that sets the camera in renderer
     *
     * @author  Diego Jesus <diego.a.r.jz@gmail.com>
     * @date    28 May 2015
     */
    class SetCameraRenderTask : public RenderTask {
    private:
        CameraPtr mCamera;
    public:
        /* ****************************
         * Construction & Destruction *
         * ***************************/
        SetCameraRenderTask(CameraPtr camera);
        virtual ~SetCameraRenderTask();
        
        virtual void Execute(RendererPtr renderer) override;
        
    }; // class LoadShaderRenderTask
    
} // namespace bde

#else
namespace bde {
    class LoadShaderRenderTask;
} // namespace bde


#endif /* defined(__BlackDogEngine__SetCameraRenderTask__) */
