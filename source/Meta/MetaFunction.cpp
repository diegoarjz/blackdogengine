//
//  MetaFunction.cpp
//  BlackDogEngine
//
//  Created by Diego Jesus on 19/06/15.
//
//

#include "MetaFunction.h"

namespace bde {
    const char* MetaFunction::Name() const {
        return mName;
    }
    
    const MetaType* MetaFunction::ReturnType() const {
        return mSignature.ReturnType();
    }
    
    const MetaType* MetaFunction::ArgumentType(U32 index) const {
        return mSignature.ArgumentType( index );
    }
    
    U32 MetaFunction::ArgumentsCount() const {
        return mSignature.ArgumentsCount();
    }
    
    const FunctionSignature& MetaFunction::GetFunctionSignature() const{
        return mSignature;
    }
    
    void MetaFunction::Apply(Variable ret, Variable *args, U32 argsCount ) const {
        mApplyWrapper(mFunction, ret, args, argsCount);
    }

    void PrintMetaFunction(MetaFunction mf) {
        PrintFunctionSignature( mf.GetFunctionSignature(), mf.Name() );
    }
    
    void PrintAllMetaFunctions(){
        auto el = MetaFunction::Head();
        
        while (el != NULL){
            
            PrintMetaFunction( *el );
            
            el = el->Next();
        }
    }
}
