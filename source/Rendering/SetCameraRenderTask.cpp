#include "SetCameraRenderTask.h"

namespace bde{
    SetCameraRenderTask::SetCameraRenderTask(CameraPtr camera){
        mCamera = camera;
    }
    
    SetCameraRenderTask::~SetCameraRenderTask(){
        
    }
    
    void SetCameraRenderTask::Execute(RendererPtr renderer){
        renderer->SetCurrentCamera(mCamera);
    }
}