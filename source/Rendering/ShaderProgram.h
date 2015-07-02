#ifndef SHADERPROGRAM_H_
#define SHADERPROGRAM_H_

#include "../Object.h"
#include "BindingInfo.h"
#include "Shader.h"

namespace bde {

    /**
     * Describes a ShaderProgram which is made of several shaders
     *
     * @author  Diego Jesus <diego.a.r.jz@gmail.com>
     * @date    28 May 2015
     */
    class ShaderProgram : public Object {
      public:
        enum class ShaderOutputType {
            ScreenBuffer,
            MAX_SHADEROUTPUT_TYPE
        };
      private:
        ShaderPtr mShaders[(int)Shader::ShaderType::MAX_SHADER_TYPES];          ///< The program's shaders
        BindingInfoPtr mBindingInfo;                                            ///< Binding information
        std::string mOutputNames[(int)ShaderOutputType::MAX_SHADEROUTPUT_TYPE]; ///< The output names
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
        void            SetOutputName(const ShaderOutputType &type,
                                      const std::string &name);
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
