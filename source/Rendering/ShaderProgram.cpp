#include "ShaderProgram.h"
#include <cassert>

namespace bde {
    RTTI_DEF(ShaderProgram, "ShaderProgram", Object);

    /* ****************************
     * Construction & Destruction *
     * ***************************/
    ShaderProgram::ShaderProgram() {
    }
	
	ShaderProgram::ShaderProgram(ShaderPtr vertexShader, ShaderPtr fragmentShader, ShaderPtr geomShader){
		mShaders[(int)Shader::ShaderType::Vertex] = vertexShader;
		mShaders[(int)Shader::ShaderType::Fragment] = fragmentShader;
		mShaders[(int)Shader::ShaderType::Geometry] = geomShader;
	}

    ShaderProgram::~ShaderProgram() {
    }

    /* *******************
     * Getters & Setters *
     * ******************/
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
    
    void ShaderProgram::AddShaderUniform(ShaderUniformPtr uniform){
        mCustomUniforms.push_back(uniform);
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
	
	RenderStatePtr ShaderProgram::GetRenderState(const RenderState::RenderStateNames &state){
		return mRenderStates[state];
	}
}