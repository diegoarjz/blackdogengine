#ifndef __BlackDogEngine__ShaderAttribute__
#define __BlackDogEngine__ShaderAttribute__

#include <string>
#include <memory>
#include <functional>

#include "Bindable.h"
#include "Renderer.h"

namespace bde {
    class ShaderAttribute;
    typedef std::shared_ptr<ShaderAttribute> ShaderAttributePtr;
    
    /**
     * A shader attribute is an engine defined value for a shader uniform.
     *
     * Examples of this are the projection, model and view matrices.
     * During rendering, the Black Dog Engine automatically retrieves these values
     * and passes them onto the shader.
     *
     * To define a ShaderAttribute, one binds a name to an attribute sementics in
     * a shader program using the following:
     *
     * ShaderProgramPtr program = ...
     * program->BindSemanticsToName( semantics, nameInShader );
     */
    class ShaderAttribute : public Bindable, public std::enable_shared_from_this<ShaderAttribute>{
    public:
        typedef std::function<void (ShaderAttributePtr, RendererPtr, GameObjectPtr)> SetValueFunction;
        
        enum Semantics{
            // Transforms
            ModelMatrix,
            ViewMatrix,
            ProjectionMatrix,
            ModelViewMatrix,
            ModelViewProjectionMatrix,
            NormalMatrix,
            MAX_SEMANTICS,
        }; // enum class ShaderUniformSemantics
    private:
        std::string mNameInShader;
        Semantics mSemantics;
        SetValueFunction mFunction;
    public:
        /* ****************************
         * Construction & Destruction *
         * ***************************/
        ShaderAttribute(const std::string &name, const Semantics &semantics);
        virtual ~ShaderAttribute();
        
        /* *******************
         * Getters & Setters *
         * ******************/
        std::string GetNameInShader() const;
        Semantics GetSemantics() const;
        
        void SetValue(RendererPtr r, GameObjectPtr go);
    }; // class ShaderAttribute
} // namespace ShaderAttribute

#else
namespace bde{
    class ShaderAttribute;
    typedef std::shared_ptr<ShaderAttribute> ShaderAttributePtr;
}
#endif /* defined(__BlackDogEngine__ShaderAttribute__) */
