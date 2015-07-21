#include "SetMaterialRenderTask.h"

namespace bde{
    /* ****************************
     * Construction & Destruction *
     * ***************************/
    SetMaterialRenderTask::SetMaterialRenderTask(MaterialPtr material, GameObjectPtr gameObject){
        mMaterial = material;
        mGameObject = gameObject;
    }
    
    SetMaterialRenderTask::~SetMaterialRenderTask(){
        
    }
    
    void SetMaterialRenderTask::Execute(RenderingDevicePtr device){
        // the material also needs some information from the game object
        device->SetMaterial( mMaterial, mGameObject );
    }
}