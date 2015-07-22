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
            if (component->NeedsUpdate()) {
                component->CalculateLocalToParentMatrix();
            }
        }
    }
    
    TransformComponentPtr TransformationSubsystem::CreateComponent(){
        auto component = std::make_shared<TransformComponent>();
        mComponents.push_back( component );
        
        return component;
    }
    
    TransformComponentPtr TransformationSubsystem::GetComponentForID(const U32 &componentId){
        return mComponents[componentId];
    }
}