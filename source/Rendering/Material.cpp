#include "Material.h"

namespace bde{
    Material::Material(ShaderProgramPtr shaderProgram){
        mShaderProgram = shaderProgram;
        
        auto uniforms = mShaderProgram->CustomUniforms();
        for(auto u : uniforms){
            auto uniformName = u->GetNameInShader();
            auto uniformValue = u->CreateShaderUniformValue();
            
            mUniformValues[uniformName] = uniformValue;
        }
    }
    
    Material::~Material(){
        
    }
    
    ShaderProgramPtr Material::GetShaderProgram(){
        return mShaderProgram;
    }
    
    Material::UniformValueTable::iterator Material::UniformValuesBegin(){
        return std::begin(mUniformValues);
    }
    
    Material::UniformValueTable::iterator Material::UniformValuesEnd(){
        return std::end(mUniformValues);
    }
} // namespace bde