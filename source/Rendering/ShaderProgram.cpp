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
    
    ShaderUniformPtr ShaderProgram::BindSemanticsToName(const ShaderUniformSemantics &semantics, const std::string &nameInShader){
//        ShaderUniformPtr uniform = std::make_shared<ShaderUniform>(nameInShader, semantics);
//        
//        mUniforms[(int)semantics] = uniform;
//        
//        return uniform;
        return nullptr;
    }
    
    ShaderUniformPtr ShaderProgram::GetUniformForSemantics(const ShaderUniformSemantics &semantics) const{
        return mUniforms[(int)semantics];
    }
    
    std::vector<ShaderUniformPtr>& ShaderProgram::CustomUniforms(){
        return mCustomUniforms;
    }
}