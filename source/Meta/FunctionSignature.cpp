//
//  FunctionSignature.cpp
//  BlackDogEngine
//
//  Created by Diego Jesus on 19/06/15.
//
//

#include "FunctionSignature.h"

#include <iostream>

namespace bde {
    /* *******************
     * Getters & Setters * 
     * ******************/
    const MetaType * FunctionSignature::ReturnType() const {
        return mReturnType;
    }
    const MetaType *FunctionSignature::ArgumentType(const int &index) const {
        return mArgumentsType[index];
    }
    U32 FunctionSignature::ArgumentsCount() const {
        return mArgumentsCount;
    }
    
    void PrintFunctionSignature(const FunctionSignature &fs, const std::string &name) {
        std::cout << fs.ReturnType()->Name() << " " << name << " ( ";
        
        for(int i=0; i<fs.ArgumentsCount(); ++i) {
            std::cout << fs.ArgumentType(i)->Name();
            
            if(i<fs.ArgumentsCount()-1) {
                std::cout << ", ";
            }
        }
        
        std::cout << " ) " << std::endl;
    }
} // namespace bde