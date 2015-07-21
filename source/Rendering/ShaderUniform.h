#ifndef __BlackDogEngine__ShaderUniform__
#define __BlackDogEngine__ShaderUniform__

#include <string>
#include <memory>
#include <functional>

#include "BindingInfo.h"
#include "ShaderUniformValue.h"
#include "../MathLib/MathLib.h"
#include "Bindable.h"

namespace bde {
    
    class ShaderUniformValueBase;
    typedef std::shared_ptr<ShaderUniformValueBase> ShaderUniformValuePtr;
    
    /**
     * Represents a shader uniform whose value can be modified by the user.
     *
     * It is a bindable to prevent fetching the location in the shader every frame.
     * It's location is stored in the associated binding info.
     *
     * Provides a method for sub classes to create typed shader uniform values.
     */
    class ShaderUniformBase : public Bindable{
    protected:
        /** 
         * The name the uniform takes in shader. It will be used to fetch its
         * location and bind it.
         */
        std::string mNameInShader;
    public:
        ShaderUniformBase(const std::string &name);
        virtual ~ShaderUniformBase();
        
        std::string GetNameInShader() const;
        
        virtual ShaderUniformValuePtr CreateShaderUniformValue() = 0;
    }; // class ShaderUniformBase
    
    /**
     * Provides a templated subclass of ShaderUniformBase.
     *
     * Because uniforms in shaders are typed, the templated class provides a way to
     * capture those types while, at the same type, providing a method to easily create
     * a typed shader uniform value which can be modified by the user.
     */
    template<typename T>
    class ShaderUniform : public ShaderUniformBase, public std::enable_shared_from_this<ShaderUniform<T>>{
    public:
        /* ****************************
         * Construction & Destruction *
         * ***************************/
        ShaderUniform(const std::string &name):ShaderUniformBase(name){
            
        }
        
        virtual ~ShaderUniform(){
            
        }
    
        /**
         * Creates a shader uniform value of the same type, allowing the easy modification of
         * its value.
         * Also useful when creating a material from a shader program.
         */
        virtual ShaderUniformValuePtr CreateShaderUniformValue() override{
            return std::make_shared<ShaderUniformValue<T>>(this->shared_from_this(), mNameInShader);
        }
    }; // class ShaderUniform
    
    typedef std::shared_ptr<ShaderUniformBase> ShaderUniformPtr;
} // namespace sel

#else

namespace bde{
    class ShaderUniformBase;
    typedef std::shared_ptr<ShaderUniformBase> ShaderUniformPtr;
} // namespace bde

#endif /* defined(__BlackDogEngine__ShaderUniform__) */
