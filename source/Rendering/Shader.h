#ifndef SHADER_H_
#define SHADER_H_

#include <string>

#include "../Object.h"
#include "BindingInfo.h"

namespace bde {

    /**
     * Holds shader information.
     *
     * @author  Diego Jesus <diego.a.r.jz@gmail.com>
     * @date    28 May 2015
     */
    class Shader :public Object {
      public:
        enum class ShaderType {
            Vertex, Fragment, Geometry, MAX_SHADER_TYPES
        }; // enum class ShaderType
      private:
        std::string     mSource;        ///< Shader's source code.
        BindingInfoPtr  mBindingInfo;   ///< Video memory binding information.
        ShaderType      mShaderType;    ///< The type of shader.
      public:
        RTTI_DECL

        /* ****************************
         * Construction & Destruction *
         * ***************************/
        Shader(const ShaderType &type);
        virtual ~Shader();

        /* *******************
         * Getters & Setters *
         * ******************/
        std::string     GetSource() const;
        void            SetSource(const std::string &source);
        ShaderType      GetShaderType() const;
        BindingInfoPtr  GetBindingInfo();
        void            SetBindingInfo(BindingInfoPtr bi);
    }; // class Shader

    typedef std::shared_ptr<Shader> ShaderPtr;
    typedef std::weak_ptr<Shader> ShaderWeakPtr;
} // namespace bde

#endif
