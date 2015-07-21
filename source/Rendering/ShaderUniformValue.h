#ifndef __BlackDogEngine__ShaderUniformValue__
#define __BlackDogEngine__ShaderUniformValue__

#include <memory>

#include "RenderingDevice.h"

namespace bde {
    
    /**
     * Base class for a shader uniform value.
     *
     * Sub classes will hold values of specific kinds and,
     * while rendering, they should set their values to the renderer.
     */
    class ShaderUniformValueBase{
    protected:
        /// Same as the name in shader.
        std::string mName;
        ShaderUniformPtr mShaderUniform;
    public:
        ShaderUniformValueBase(ShaderUniformPtr uniform, const std::string &name);
        
        virtual void Set(RenderingDevicePtr r) = 0;
    }; // class ShaderUniformValueBase
    typedef std::shared_ptr<ShaderUniformValueBase> ShaderUniformValuePtr;
    
    /**
     * Templated shader uniform value to hold different types of values.
     *
     * While the ShaderUniformValueBase class holds the information about the shader uniform, 
     * this templated class holds information about the value that uniform has.
     */
    template<typename T>
    class ShaderUniformValue : public ShaderUniformValueBase{
    private:
        T mValue;
    public:
        /* ****************************
         * Construction & Destruction *
         * ***************************/
        ShaderUniformValue(ShaderUniformPtr uniform, const std::string &name): ShaderUniformValueBase(uniform, name){
   
        }
        
        /* *******************
         * Getters & Setters *
         * ******************/
        T GetValue() const{
            return mValue;
        }
        
        void SetValue(const T &value){
            mValue = value;
        }
        
        virtual void Set(RenderingDevicePtr r) override{
            r->SetUniformValue(mShaderUniform, mValue);
        }
    };
} // namespace  bde

#endif /* defined(__BlackDogEngine__ShaderUniformValue__) */
