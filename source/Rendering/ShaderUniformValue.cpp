//
//  ShaderUniformValue.cpp
//  BlackDogEngine
//
//  Created by Diego Jesus on 06/07/15.
//
//

#include "ShaderUniformValue.h"

namespace bde{
    
    ShaderUniformValueBase::ShaderUniformValueBase(ShaderUniformPtr uniform, const std::string &name){
        mName = name;
        mShaderUniform = uniform;
    }
    
} // namespace bde