#include "ShaderAttribute.h"

#include "../TransformationSubsystem.h"
#include "../TransformComponent.h"

namespace bde{
    ShaderAttribute::SetValueFunction setValueFunctions[] = {
        // ModelMatrix
        [](ShaderAttributePtr attr, RenderingDevicePtr r, GameObjectPtr go) {
            auto transformComponent = go->GetComponent<TransformComponent>();
            auto matrix = transformComponent->GetLocalToWorldMatrix();
            r->SetAttributeValue(attr, matrix);
        },
        // ViewMatrix
        [](ShaderAttributePtr attr, RenderingDevicePtr r, GameObjectPtr go) {},
        // ProjectionMatrix
        [](ShaderAttributePtr attr, RenderingDevicePtr r, GameObjectPtr go) {},
        // ModelViewMatrix
        [](ShaderAttributePtr attr, RenderingDevicePtr r, GameObjectPtr go) {},
        // ModelViewProjectionMatrix
        [](ShaderAttributePtr attr, RenderingDevicePtr r, GameObjectPtr go) {},
        // NormalMatrix
        [](ShaderAttributePtr attr, RenderingDevicePtr r, GameObjectPtr go) {},
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
    
    void ShaderAttribute::SetValue(RenderingDevicePtr r, GameObjectPtr go){
        mFunction(shared_from_this(), r, go);
    }
} // namespace bde