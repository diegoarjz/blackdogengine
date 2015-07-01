//
//  MetaMemberFunction.h
//  BlackDogEngine
//
//  Created by Diego Jesus on 19/06/15.
//
//

#ifndef __BlackDogEngine__MetaMemberFunction__
#define __BlackDogEngine__MetaMemberFunction__

#include <stdio.h>

#include "FunctionSignature.h"
#include "MetaType.h"
#include "Variable.h"
#include "ApplyToObject.h"

namespace bde {
    
    template<class C, typename Fun>
    void ApplyToObjectWrapper(void (C::*fun) (void), C *object,Variable retVal, Variable *args, U32 argCount){
        ApplyToObject::Apply(object, (Fun)fun , retVal, args, argCount);
    }
    
    class MetaMemberFunctionBase {
        
    public:
        
        virtual void ApplyToObject(void *object, Variable retVal, Variable *args, U32 argCount) = 0;
    };
    
    template<class C>
    class MetaMemberFunction : public MetaMemberFunctionBase{
    private:
        const char* mName;
        void (C::*mFunction) (void);
        void (*mApplyToObjectWrapper) (void (C::*) (void), C*, Variable, Variable*, U32);
        const MetaType *mReturnType;
        const MetaType **mArgumentTypes;
        U32 mNumArguments;
        
    public:
        MetaMemberFunction(const char* name){
            mName = name;
        }
        
        template<typename Ret>
        MetaMemberFunction(const char* name, Ret(C::*memberFunction)() ){
            mName = name;
            mFunction = (void (C::*) ())(memberFunction);
            mReturnType = &GetMetaTypeByType<Ret>();
            mApplyToObjectWrapper = ApplyToObjectWrapper<C, Ret(C::*)()>;
            mArgumentTypes = NULL;
            mNumArguments = 0;
        }
        
        const char* Name() const{
            return mName;
        }
        
        const MetaType* ReturnType() const{
            return mReturnType;
        }
        
        virtual void ApplyToObject(void *object, Variable retVal, Variable *args, U32 argCount) override{
            mApplyToObjectWrapper(mFunction, (C*)object, retVal, args, argCount);
        }
    };
}
#endif /* defined(__BlackDogEngine__MetaMemberFunction__) */
