#include "TransformationSubsystem.h"

namespace bde{
    TransformationSubsystem::TransformationSubsystem(){
        
    }
    
    TransformationSubsystem::~TransformationSubsystem(){
        
    }
    
    void TransformationSubsystem::Init(){
        
    }
    
    void TransformationSubsystem::Terminate(){
        
    }
    
    void TransformationSubsystem::Update(const TIME_T &delta){
        for(auto component : mComponents){
            if (component.NeedsUpdate()) {
                component.CalculateLocalToParentMatrix();
            }
        }
    }
    
    std::shared_ptr<TransformationSubsystem::transform_handle_t> TransformationSubsystem::CreateComponent(){
#warning TODO: the id calculation is not correct.
        mComponents.push_back( TransformComponent() );
        
        return std::make_shared<transform_handle_t>(this, mComponents.size()-1);
    }
    
    TransformComponent* TransformationSubsystem::GetComponentForID(const U32 &componentId){
        return &(mComponents[componentId]);
    }
}