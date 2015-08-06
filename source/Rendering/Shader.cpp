#include "Shader.h"

namespace bde {
    RTTI_DEF(Shader, "Shader", Object);

    /* ****************************
     * Construction & Destruction *
     * ***************************/
    Shader::Shader(const ShaderType &type) {
        mShaderType = type;
    }
	
	Shader::Shader(const ShaderType &type, const std::string &source){
		mShaderType = type;
		mSource = source;
	}

    Shader::~Shader() {
    }

    /* *******************
     * Getters & Setters *
     * ******************/
    const std::string& Shader::GetSource() const {
        return mSource;
    }

    void        Shader::SetSource(const std::string &source) {
        mSource = source;
    }

    Shader::ShaderType      Shader::GetShaderType() const {
        return mShaderType;
    }
} // namespace bde