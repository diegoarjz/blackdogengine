#ifndef __BlackDogEngine__ShaderUniform__
#define __BlackDogEngine__ShaderUniform__

#include <string>
#include <memory>
#include <functional>

#include "BindingInfo.h"
#include "../MathLib/MathLib.h"

namespace bde {
    
    class ShaderUniformValueBase;
    typedef std::shared_ptr<ShaderUniformValueBase> ShaderUniformValuePtr;
    
    class RenderingDevice;
    typedef std::shared_ptr<RenderingDevice> RenderingDevicePtr;
    
    typedef std::function<void (RenderingDevicePtr)> UniformBindingFunction;
    
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
    private:
    public:
        virtual ShaderUniformValuePtr CreateShaderUniformValue() = 0;
    }; // class ShaderUniformBase
    
    /**
     * Provides binding information between a material uniform 
     * semantics and the shader program that uses it.
     */
    class ShaderUniform : public ShaderUniformBase, public std::enable_shared_from_this<ShaderUniform>{
    public:
        enum class ShaderUniformType{
            FloatUniform,
            Vector2Uniform,
            Vector3Uniform,
            Vector4Uniform,
            QuaternionUniform,
            ColorRGBUniform,
            ColorRGBAUniform,
            Matrix3Uniform,
            Matrix4Uniform,
        };
    private:
        std::string mNameInShader;
        ShaderUniformSemantics mSemantics;
        BindingInfoPtr mBindingInfo;
        UniformBindingFunction mBindingFunction;
        ShaderUniformType mType;
    public:
        /* ****************************
         * Construction & Destruction *
         * ***************************/
        ShaderUniform(const std::string &name, const ShaderUniformSemantics &semantics);
        ShaderUniform(const ShaderUniformType &type, const std::string &name);
        ~ShaderUniform();
        
        /* *******************
         * Getters & Setters *
         * ******************/
        BindingInfoPtr GetBindingInfo() const;
        void SetBindingInfo(BindingInfoPtr bi);
        std::string GetNameInShader() const;
        ShaderUniformType GetType() const;
        
        virtual ShaderUniformValuePtr CreateShaderUniformValue() override;
        
        void SetValue(RenderingDevicePtr r, const float& f);
        void SetValue(RenderingDevicePtr r, const Vector2 &v);
        void SetValue(RenderingDevicePtr r, const Vector3 &v);
        void SetValue(RenderingDevicePtr r, const Vector4 &v);
        void SetValue(RenderingDevicePtr r, const Quaternion &q);
        void SetValue(RenderingDevicePtr r, const ColorRGB &c);
        void SetValue(RenderingDevicePtr r, const ColorRGBA &c);
        void SetValue(RenderingDevicePtr r, const Matrix3 &m);
        void SetValue(RenderingDevicePtr r, const Matrix4 &m);
    }; // class ShaderUniform
    
    typedef std::shared_ptr<ShaderUniform> ShaderUniformPtr;
} // namespace sel

#else

namespace bde{
    class ShaderUniform;
    typedef std::shared_ptr<ShaderUniform> ShaderUniformPtr;
} // namespace bde

#endif /* defined(__BlackDogEngine__ShaderUniform__) */
