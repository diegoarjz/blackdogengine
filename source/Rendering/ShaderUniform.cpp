#include "ShaderUniform.h"

#include "RenderingDevice.h"
#include "ShaderUniformValue.h"

namespace bde {
    ShaderUniformBase::ShaderUniformBase(const std::string &name){
        mNameInShader = name;
    }
    
    ShaderUniformBase::~ShaderUniformBase(){
        
    }
    
    std::string ShaderUniformBase::GetNameInShader() const{
        return mNameInShader;
    }
}
