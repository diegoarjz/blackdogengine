#include "ShaderUniform.h"

#include "RenderingDevice.h"
#include "ShaderUniformValue.h"
#include "../MathLib/MathLib.h"

namespace bde {
    ShaderUniformBase::ShaderUniformBase(const std::string &name){
        mNameInShader = name;
    }
    
    ShaderUniformBase::~ShaderUniformBase(){
        
    }
    
    std::string ShaderUniformBase::GetNameInShader() const{
        return mNameInShader;
    }
    
    BindingInfoPtr ShaderUniformBase::GetBindingInfo() const{
        return mBindingInfo;
    }
    
    void ShaderUniformBase::SetBindingInfo(BindingInfoPtr bi){
        mBindingInfo = bi;
    }
}