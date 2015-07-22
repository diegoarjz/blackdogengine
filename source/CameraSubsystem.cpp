#include "CameraSubsystem.h"
#include "TransformComponent.h"

namespace bde {
    /* ****************************
     * Construction & Destruction *
     * ***************************/
    CameraSubsystem::CameraSubsystem(){
        
    }
    CameraSubsystem::~CameraSubsystem(){
        
    }
    
    void CameraSubsystem::Init() {
        
    }
    
    void CameraSubsystem::Terminate() {
        
    }
    
    /**
     * Updates the transformation matrix of all components
     * that require update.
     */
    void CameraSubsystem::Update(const TIME_T &delta) {
        for(auto camera : mComponents){
            camera->OnFrameChanged();
            camera->OnFrustumChanged();
        }
    }
    
    CameraPtr CameraSubsystem::CreateComponent(){
        auto camera = std::make_shared<Camera>();
        mComponents.push_back(camera);
        
        return camera;
    }
    
    CameraPtr CameraSubsystem::GetComponentForID(const U32 &componentId){
        if(componentId > mComponents.size()){
            return nullptr;
        }
        
        return mComponents[componentId];
    }
}