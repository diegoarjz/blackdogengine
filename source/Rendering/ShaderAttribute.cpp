#include "ShaderAttribute.h"

#include "../TransformationSubsystem.h"
#include "../TransformComponent.h"

namespace bde{
    ShaderAttribute::SetValueFunction setValueFunctions[] = {
        // ModelMatrix
        [](ShaderAttributePtr attr, RendererPtr r, GameObjectPtr go) {
            auto transformComponent = go->GetComponent<TransformComponent>();
            auto matrix = transformComponent->GetLocalToWorldMatrix();
            r->GetRenderingDevice()->SetAttributeValue(attr, matrix);
        },
        // ViewMatrix
        [](ShaderAttributePtr attr, RendererPtr r, GameObjectPtr go) {
            auto cam = r->GetCurrentCamera();
            auto matrix = cam->GetViewMatrix();
            r->GetRenderingDevice()->SetAttributeValue(attr, matrix);
        },
        // ProjectionMatrix
        [](ShaderAttributePtr attr, RendererPtr r, GameObjectPtr go) {
            auto cam = r->GetCurrentCamera();
            auto matrix = cam->GetProjectionMatrix();
            r->GetRenderingDevice()->SetAttributeValue(attr, matrix);},
        // ModelViewMatrix
        [](ShaderAttributePtr attr, RendererPtr r, GameObjectPtr go) {
            auto cam = r->GetCurrentCamera();
            auto transformComponent = go->GetComponent<TransformComponent>();
            auto model = transformComponent->GetLocalToWorldMatrix();
            auto view = cam->GetViewMatrix();
            r->GetRenderingDevice()->SetAttributeValue(attr, model*view);
        },
        // ModelViewProjectionMatrix
        [](ShaderAttributePtr attr, RendererPtr r, GameObjectPtr go) {
            auto cam = r->GetCurrentCamera();
            auto transformComponent = go->GetComponent<TransformComponent>();
            auto model = transformComponent->GetLocalToWorldMatrix();
            auto view = cam->GetViewMatrix();
            auto projection = cam->GetProjectionMatrix();
            r->GetRenderingDevice()->SetAttributeValue(attr, model*view*projection);
        },
        // NormalMatrix
        [](ShaderAttributePtr attr, RendererPtr r, GameObjectPtr go) {},
    };
    
    ShaderAttribute::ShaderAttribute(const std::string &name,
                                     const Semantics &semantics){
        mNameInShader = name;
        mSemantics = semantics;
        mFunction = setValueFunctions[mSemantics];
    }
    
    ShaderAttribute::~ShaderAttribute(){
        
    }
    
    std::string ShaderAttribute::GetNameInShader() const{
        return mNameInShader;
    }
    
    ShaderAttribute::Semantics ShaderAttribute::GetSemantics() const{
        return mSemantics;
    }
    
    void ShaderAttribute::SetValue(RendererPtr r, GameObjectPtr go){
        mFunction(shared_from_this(), r, go);
    }
} // namespace bde