#include "ShaderUniform.h"

#include "RenderingDevice.h"
#include "ShaderUniformValue.h"
#include "../MathLib/MathLib.h"

namespace bde {
    UniformBindingFunction shaderUniformBindingFunctions[(int)ShaderUniformSemantics::MAX_UNIFORMS] = {
        [](RenderingDevicePtr d){ /**/ },
        [](RenderingDevicePtr d){ /**/ },
        [](RenderingDevicePtr d){ /**/ },
        [](RenderingDevicePtr d){ /**/ },
        [](RenderingDevicePtr d){ /**/ },
        [](RenderingDevicePtr d){ /**/ },
    };
    
    /* ****************************
     * Construction & Destruction *
     * ***************************/
    ShaderUniform::ShaderUniform(const std::string &name, const ShaderUniformSemantics &semantics){
        mNameInShader = name;
        mSemantics = semantics;
        mBindingFunction = shaderUniformBindingFunctions[(int)semantics];
    }
    
//    ShaderUniform::ShaderUniform(const std::string &name, UniformBindingFunction bindingFunction){
//        mNameInShader = name;
//        mSemantics = ShaderUniformSemantics::Custom;
//        mBindingFunction = bindingFunction;
//    }
    
    ShaderUniform::ShaderUniform(const ShaderUniformType &type, const std::string &name){
        mType = type;
        mNameInShader = name;
    }
    
    ShaderUniform::~ShaderUniform(){
        
    }
    
    /* *******************
     * Getters & Setters *
     * ******************/
    BindingInfoPtr ShaderUniform::GetBindingInfo() const{
        return mBindingInfo;
    }
    
    void ShaderUniform::SetBindingInfo(BindingInfoPtr bi){
        mBindingInfo = bi;
    }
    
    std::string ShaderUniform::GetNameInShader() const{
        return mNameInShader;
    }
    
    ShaderUniform::ShaderUniformType ShaderUniform::GetType() const{
        return mType;
    }
    
    ShaderUniformValuePtr ShaderUniform::CreateShaderUniformValue(){
        switch (mType) {
            case ShaderUniformType::FloatUniform:
                return std::make_shared<ShaderUniformValue<float>>(shared_from_this(), mNameInShader);
                break;
            case ShaderUniformType::Vector2Uniform:
                return std::make_shared<ShaderUniformValue<Vector2>>(shared_from_this(), mNameInShader);
                break;
            case ShaderUniformType::Vector3Uniform:
                return std::make_shared<ShaderUniformValue<Vector3>>(shared_from_this(), mNameInShader);
                break;
            case ShaderUniformType::Vector4Uniform:
                return std::make_shared<ShaderUniformValue<Vector4>>(shared_from_this(), mNameInShader);
                break;
            case ShaderUniformType::QuaternionUniform:
                return std::make_shared<ShaderUniformValue<Quaternion>>(shared_from_this(), mNameInShader);
                break;
            case ShaderUniformType::ColorRGBUniform:
                return std::make_shared<ShaderUniformValue<ColorRGB>>(shared_from_this(), mNameInShader);
                break;
            case ShaderUniformType::ColorRGBAUniform:
                return std::make_shared<ShaderUniformValue<ColorRGBA>>(shared_from_this(), mNameInShader);
                break;
            case ShaderUniformType::Matrix3Uniform:
                return std::make_shared<ShaderUniformValue<Matrix3>>(shared_from_this(), mNameInShader);
                break;
            case ShaderUniformType::Matrix4Uniform:
                return std::make_shared<ShaderUniformValue<Matrix4>>(shared_from_this(), mNameInShader);
                break;
        }
        return nullptr;
    }
    
    void ShaderUniform::SetValue(RenderingDevicePtr r, const float& f){
        r->SetUniformValue(shared_from_this(), f);
    }
    
    void ShaderUniform::SetValue(RenderingDevicePtr r, const Vector2 &v){
        r->SetUniformValue(shared_from_this(), v);
    }
    
    void ShaderUniform::SetValue(RenderingDevicePtr r, const Vector3 &v){
        r->SetUniformValue(shared_from_this(), v);
    }
    
    void ShaderUniform::SetValue(RenderingDevicePtr r, const Vector4 &v){
        r->SetUniformValue(shared_from_this(), v);
    }
    
    void ShaderUniform::SetValue(RenderingDevicePtr r, const Quaternion &q){
        r->SetUniformValue(shared_from_this(), q);
    }
    
    void ShaderUniform::SetValue(RenderingDevicePtr r, const ColorRGB &c){
        r->SetUniformValue(shared_from_this(), c);
    }
    
    void ShaderUniform::SetValue(RenderingDevicePtr r, const ColorRGBA &c){
        r->SetUniformValue(shared_from_this(), c);
    }
    
    void ShaderUniform::SetValue(RenderingDevicePtr r, const Matrix3 &m){
        r->SetUniformValue(shared_from_this(), m);
    }
    
    void ShaderUniform::SetValue(RenderingDevicePtr r, const Matrix4 &m){
        r->SetUniformValue(shared_from_this(), m);
    }
    
}