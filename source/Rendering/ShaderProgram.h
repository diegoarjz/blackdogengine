#ifndef SHADERPROGRAM_H_
#define SHADERPROGRAM_H_

#include <list>
#include <vector>
#include <string>

#include "../Object.h"
#include "BindingInfo.h"
#include "Shader.h"
#include "ShaderUniform.h"
#include "ShaderAttribute.h"

namespace bde {

    /**
     * Describes a ShaderProgram which is made of several shaders
     */
    class ShaderProgram : public Object {
      public:
        enum class ShaderOutputType {
            ScreenBuffer,
            MAX_SHADEROUTPUT_TYPE
        };
      private:
        ShaderPtr mShaders[(int)Shader::ShaderType::MAX_SHADER_TYPES];          ///< The program's shaders
        std::string mOutputNames[(int)ShaderOutputType::MAX_SHADEROUTPUT_TYPE]; ///< The output names
        ShaderAttributePtr mAttributes[ShaderAttribute::Semantics::MAX_SEMANTICS];
        std::vector<ShaderUniformPtr> mCustomUniforms;                          ///< The user defined uniforms.
        BindingInfoPtr mBindingInfo;                                            ///< Binding information
      public:
        RTTI_DECL

        /* ****************************
         * Construction & Destruction *
         * ***************************/
        ShaderProgram();
        virtual ~ShaderProgram();

        /* *******************
         * Getters & Setters *
         * ******************/
        BindingInfoPtr  GetBindingInfo();
        void            SetBindingInfo(BindingInfoPtr bi);
        ShaderPtr       GetShader(const Shader::ShaderType &type);
        void            SetShader(const Shader::ShaderType &type, ShaderPtr shader);
        std::string     GetOutputName(const ShaderOutputType &type);
        void            SetOutputName(const ShaderOutputType &type, const std::string &name);
        
        ShaderAttributePtr BindSemanticsToName(const ShaderAttribute::Semantics &semantics, const std::string &nameInShader);
        ShaderAttributePtr GetAttributeForSemantics(const ShaderAttribute::Semantics &semantics) const;

        void AddShaderUniform(ShaderUniformPtr uniform);
        std::vector<ShaderUniformPtr>& CustomUniforms();
    }; // class ShaderProgram

    typedef std::shared_ptr<ShaderProgram>  ShaderProgramPtr;
    typedef std::weak_ptr<ShaderProgram>    ShaderProgramWeakPtr;

} // namespace bde

#else
namespace bde {
    class ShaderProgram;
    typedef std::shared_ptr<ShaderProgram>  ShaderProgramPtr;
    typedef std::weak_ptr<ShaderProgram>    ShaderProgramWeakPtr;
} // namespace bde
#endif
