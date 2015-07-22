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
    
    void SetMaterialRenderTask::Execute(RendererPtr renderer){
        // the material also needs some information from the game object
        
        auto renderingDevice = renderer->GetRenderingDevice();
        // First, set the shader program
        renderingDevice->SetShaderProgram(mMaterial->GetShaderProgram());
        
        // then, set all custom uniforms
        auto uniformsIter = mMaterial->UniformValuesBegin();
        auto uniformsEndIter = mMaterial->UniformValuesEnd();
        for(/**/; uniformsIter != uniformsEndIter; ++uniformsIter){
            uniformsIter->second->Set( renderingDevice );
        }
        
        // and set the attributes
        auto shaderProgram = mMaterial->GetShaderProgram();
        // Load the attributes
        for(int i=0; i<ShaderAttribute::Semantics::MAX_SEMANTICS; ++i){
            auto attribute = shaderProgram->GetAttributeForSemantics((ShaderAttribute::Semantics)i);
            
            if(!attribute) continue;
            
            attribute->SetValue(renderer, mGameObject);
        }
    }
}