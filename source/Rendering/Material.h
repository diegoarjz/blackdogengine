#ifndef __BlackDogEngine__Material__
#define __BlackDogEngine__Material__

#include <stdio.h>
#include <map>

#include "ShaderProgram.h"
#include "ShaderUniformValue.h"
#include "ShaderAttribute.h"
#include "../Debug/Logger.h"

namespace bde {
    /**
     * Defines a material.
     *
     * Contains a set of uniform values, that will be set on the shader program
     * when rendering.
     *
     * Example usage:
     *
     * ShaderProgramPtr aShaderProgram = <fetch this somewhere>;
     * MaterialPtr material = std::make_shared<Material>(aShaderProgra);
     * auto colorUniform = material->GetUniform<ColorRGB>("color");
     * colorUniform->SetValue(colorValue);
     *
     * Because fetching the uniform by name is an expensive task, keeping a
     * pointer to it is recommended when performing successive alterations.
     */
    class Material{
    public:
        typedef std::map<std::string, ShaderUniformValuePtr> UniformValueTable;
    private:
        /// The shader responsible for rendering.
        ShaderProgramPtr mShaderProgram;
        /// The user-defined uniforms.
        UniformValueTable mUniformValues;
    public:
        /* ****************************
         * Construction & Destruction *
         * ***************************/
        Material(ShaderProgramPtr shaderProgram);
        ~Material();
        
        /* *******************
         * Getters & Setters *
         * ******************/
        ShaderProgramPtr GetShaderProgram();
        template<typename T>
        std::shared_ptr<ShaderUniformValue<T>> GetUniform(const std::string &name){
            auto iter = mUniformValues.find( name );
            if(iter == std::end( mUniformValues )){
                LOG_ERROR("Could not find uniform with name");
                return nullptr;
            }
            
            return std::dynamic_pointer_cast< ShaderUniformValue<T> >(iter->second);
        }
        
        UniformValueTable::iterator UniformValuesBegin();
        UniformValueTable::iterator UniformValuesEnd();
    }; // class Material
    
    typedef std::shared_ptr<Material> MaterialPtr;
} // namespace bde

#endif /* defined(__BlackDogEngine__Material__) */
