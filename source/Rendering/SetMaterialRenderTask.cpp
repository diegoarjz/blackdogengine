#include "SetMaterialRenderTask.h"

namespace bde{
    /* ****************************
     * Construction & Destruction *
     * ***************************/
    SetMaterialRenderTask::SetMaterialRenderTask(MaterialPtr material){
        mMaterial = material;
    }
    
    SetMaterialRenderTask::~SetMaterialRenderTask(){
        
    }
    
    void SetMaterialRenderTask::Execute(RenderingDevicePtr device){
        device->SetMaterial( mMaterial );
    }
}