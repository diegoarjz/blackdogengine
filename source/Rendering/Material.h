#ifndef __BlackDogEngine__Material__
#define __BlackDogEngine__Material__

#include <stdio.h>
#include <map>

#include "ShaderProgram.h"
#include "ShaderUniformValue.h"
#include "../Debug/Logger.h"

namespace bde {
    /**
     * Defines a material.
     *
     */
    class Material{
    public:
        typedef std::map<std::string, ShaderUniformValuePtr> UniformValueTable;
    private:
        ShaderProgramPtr mShaderProgram;
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
                LOG_ERROR("Could not find unifor with name");
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
