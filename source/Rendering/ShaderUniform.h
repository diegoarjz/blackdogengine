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
    
    class ShaderUniformBase : public Bindable{
    protected:
        std::string mNameInShader;
    public:
        ShaderUniformBase(const std::string &name);
        virtual ~ShaderUniformBase();
        
        std::string GetNameInShader() const;
        
        virtual ShaderUniformValuePtr CreateShaderUniformValue() = 0;
    }; // class ShaderUniformBase
    
    /**
     * Provides binding information between a material uniform 
     * semantics and the shader program that uses it.
     */
    template<typename T>
    class ShaderUniform : public ShaderUniformBase, public std::enable_shared_from_this<ShaderUniform<T>>{
    private:
        std::string mNameInShader;
    public:
        /* ****************************
         * Construction & Destruction *
         * ***************************/
        ShaderUniform(const std::string &name):ShaderUniformBase(name){
            
        }
        
        virtual ~ShaderUniform(){
            
        }
    
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
