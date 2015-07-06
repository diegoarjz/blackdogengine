#ifndef __BlackDogEngine__ShaderUniformValue__
#define __BlackDogEngine__ShaderUniformValue__

#include <memory>

#include "ShaderUniform.h"

namespace bde {
    
    class ShaderUniformValueBase{
    protected:
        std::string mName;
        ShaderUniformPtr mShaderUniform;
    public:
        ShaderUniformValueBase(ShaderUniformPtr uniform, const std::string &name);
        
        virtual void Set(RenderingDevicePtr r) = 0;
    }; // class ShaderUniformValueBase
    
    typedef std::shared_ptr<ShaderUniformValueBase> ShaderUniformValuePtr;
    
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
            mShaderUniform->SetValue(r, mValue);
        }
    };
} // namespace  bde

#endif /* defined(__BlackDogEngine__ShaderUniformValue__) */
