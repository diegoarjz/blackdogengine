#ifndef SHADERPROGRAM_H_
#define SHADERPROGRAM_H_

#include <list>
#include <vector>
#include <string>

#include "../Object.h"
#include "Bindable.h"
#include "Shader.h"
#include "ShaderUniform.h"
#include "ShaderAttribute.h"

#include "../Meta/AutoLister.h"

#include "RenderStatesTypeList.h"

namespace bde {

    /**
     * Describes a ShaderProgram which is made of several shaders
     */
    class ShaderProgram : public Object, public Bindable {
      public:
        enum class ShaderOutputType {
            ScreenBuffer,
            MAX_SHADEROUTPUT_TYPE
        };
      private:
        ShaderPtr mShaders[(int)Shader::ShaderType::MAX_SHADER_TYPES];          		///< The program's shaders.
        std::string mOutputNames[(int)ShaderOutputType::MAX_SHADEROUTPUT_TYPE]; 		///< The output names.
        ShaderAttributePtr mAttributes[ShaderAttribute::Semantics::MAX_SEMANTICS];		///< The engine defined uniform.
        std::vector<ShaderUniformPtr> mCustomUniforms;                          		///< The user defined uniforms.
		RenderStatePtr mRenderStates[RenderStatesTypeList::renderStatesCount];			///< The render states.
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
        ShaderPtr       GetShader(const Shader::ShaderType &type);
        void            SetShader(const Shader::ShaderType &type, ShaderPtr shader);
        std::string     GetOutputName(const ShaderOutputType &type);
        void            SetOutputName(const ShaderOutputType &type, const std::string &name);
        
        ShaderAttributePtr BindSemanticsToName(const ShaderAttribute::Semantics &semantics, const std::string &nameInShader);
        ShaderAttributePtr GetAttributeForSemantics(const ShaderAttribute::Semantics &semantics) const;

        void AddShaderUniform(ShaderUniformPtr uniform);
        std::vector<ShaderUniformPtr>& CustomUniforms();
		
		RenderStatePtr GetRenderState(const RenderState::RenderStateNames &state);
		
		template<typename RS>
		std::shared_ptr<RS> GetRenderState(){
			return std::dynamic_pointer_cast<RS>( mRenderStates[RenderStatesTypeList::IndexOfType<RS>()] );
		}
		
		template<typename RS>
		void SetRenderState(std::shared_ptr<RS> state){
			mRenderStates[RenderStatesTypeList::IndexOfType<RS>()] = state;
		}
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
