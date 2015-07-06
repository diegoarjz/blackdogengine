#include "ShaderAttribute.h"

namespace bde{
    SetValueFunction setValueFunctions[] = {
        [](RenderingDevicePtr r) {},
        [](RenderingDevicePtr r) {},
        [](RenderingDevicePtr r) {},
        [](RenderingDevicePtr r) {},
        [](RenderingDevicePtr r) {},
        [](RenderingDevicePtr r) {},
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
    
    void ShaderAttribute::SetValue(RenderingDevicePtr r){
        mFunction(r);
    }
} // namespace bde