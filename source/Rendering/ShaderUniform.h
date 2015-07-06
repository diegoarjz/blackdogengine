#ifndef __BlackDogEngine__ShaderUniform__
#define __BlackDogEngine__ShaderUniform__

#include <string>
#include <memory>
#include <functional>

#include "BindingInfo.h"
#include "ShaderUniformValue.h"
#include "../MathLib/MathLib.h"

namespace bde {
    
    class ShaderUniformValueBase;
    typedef std::shared_ptr<ShaderUniformValueBase> ShaderUniformValuePtr;
    
    enum class ShaderUniformSemantics{
        // Transforms
        ModelMatrix,
        ViewMatrix,
        ProjectionMatrix,
        ModelViewMatrix,
        ModelViewProjectionMatrix,
        NormalMatrix,
        MAX_UNIFORMS,
        // User Defined
        Custom
    }; // enum class ShaderUniformSemantics
    
    class ShaderUniformBase{
    protected:
        std::string mNameInShader;
        BindingInfoPtr mBindingInfo;
    public:
        ShaderUniformBase(const std::string &name);
        virtual ~ShaderUniformBase();
        
        std::string GetNameInShader() const;
        BindingInfoPtr GetBindingInfo() const;
        void SetBindingInfo(BindingInfoPtr bi);
        
        virtual ShaderUniformValuePtr CreateShaderUniformValue() = 0;
    }; // class ShaderUniformBase
    
    /**
     * Provides binding information between a material uniform 
     * semantics and the shader program that uses it.
     */
    template<typename T>
    class ShaderUniform : public ShaderUniformBase, public std::enable_shared_from_this<ShaderUniform<T>>{
    public:
//        enum class ShaderUniformType{
//            FloatUniform,
//            Vector2Uniform,
//            Vector3Uniform,
//            Vector4Uniform,
//            QuaternionUniform,
//            ColorRGBUniform,
//            ColorRGBAUniform,
//            Matrix3Uniform,
//            Matrix4Uniform,
//        };
    private:
        std::string mNameInShader;
        ShaderUniformSemantics mSemantics;
    public:
        /* ****************************
         * Construction & Destruction *
         * ***************************/
        ShaderUniform(const std::string &name, const ShaderUniformSemantics &semantics):ShaderUniformBase(name){
            mSemantics = semantics;
        }
        
        ShaderUniform(const std::string &name):ShaderUniformBase(name){
            mSemantics = ShaderUniformSemantics::Custom;
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
