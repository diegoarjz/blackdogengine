#include "ShaderProgram.h"
#include <cassert>

namespace bde {
    RTTI_DEF(ShaderProgram, "ShaderProgram", Object);

    /* ****************************
     * Construction & Destruction *
     * ***************************/
    ShaderProgram::ShaderProgram() {
    }

    ShaderProgram::~ShaderProgram() {
    }

    /* *******************
     * Getters & Setters *
     * ******************/
    BindingInfoPtr  ShaderProgram::GetBindingInfo() {
        return mBindingInfo;
    }

    void            ShaderProgram::SetBindingInfo(BindingInfoPtr bi) {
        assert( mBindingInfo == nullptr );
        mBindingInfo = bi;
    }

    ShaderPtr       ShaderProgram::GetShader(const Shader::ShaderType &type) {
        return mShaders[ (int) type ];
    }

    void            ShaderProgram::SetShader(const Shader::ShaderType &type,
            ShaderPtr shader) {
        mShaders[ (int) type ] = shader;
    }

    std::string     ShaderProgram::GetOutputName(const ShaderOutputType &type) {
        return mOutputNames[ (int) type ];
    }

    void            ShaderProgram::SetOutputName(const ShaderOutputType &type,
            const std::string &name) {
        mOutputNames[ (int) type ] = name;
    }
    
    std::vector<ShaderUniformPtr>& ShaderProgram::CustomUniforms(){
        return mCustomUniforms;
    }
    
    ShaderAttributePtr ShaderProgram::BindSemanticsToName(const ShaderAttribute::Semantics &semantics, const std::string &nameInShader){
        mAttributes[semantics] = std::make_shared<ShaderAttribute>(nameInShader, semantics);
        
        return mAttributes[semantics];
    }
    
    ShaderAttributePtr ShaderProgram::GetAttributeForSemantics(const ShaderAttribute::Semantics &semantics) const{
        return mAttributes[semantics];
    }
}