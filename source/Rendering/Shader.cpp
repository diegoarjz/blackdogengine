#include "Shader.h"

namespace bde {
    RTTI_DEF(Shader, "Shader", Object);

    /* ****************************
     * Construction & Destruction *
     * ***************************/
    Shader::Shader(const ShaderType &type) {
        mShaderType = type;
    }

    Shader::~Shader() {
    }

    /* *******************
     * Getters & Setters *
     * ******************/
    std::string Shader::GetSource() const {
        return mSource;
    }

    void        Shader::SetSource(const std::string &source) {
        mSource = source;
    }

    Shader::ShaderType      Shader::GetShaderType() const {
        return mShaderType;
    }
} // namespace bde