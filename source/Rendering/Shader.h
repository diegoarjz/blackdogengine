#ifndef SHADER_H_
#define SHADER_H_

#include <string>

#include "../Object.h"
#include "Bindable.h"

namespace bde {

    /**
     * Holds shader source and type information.
     */
    class Shader :public Object, public Bindable {
      public:
        enum class ShaderType {
            Vertex, Fragment, Geometry, MAX_SHADER_TYPES
        }; // enum class ShaderType
      private:
        std::string     mSource;        ///< Shader's source code.
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
        const std::string& GetSource() const;
        void SetSource(const std::string &source);
        ShaderType GetShaderType() const;
    }; // class Shader

    typedef std::shared_ptr<Shader> ShaderPtr;
    typedef std::weak_ptr<Shader> ShaderWeakPtr;
} // namespace bde

#endif
