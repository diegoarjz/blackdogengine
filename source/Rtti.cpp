//
//  Rtti.cpp
//  BlackDogEngine
//
//  Created by Diego Jesus on 10/1/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "Rtti.h"

namespace bde {

    Rtti::Rtti(const std::string &name, const Rtti* baseType){
        mName = name;
        mBaseType = baseType;
    }
    
    Rtti::~Rtti(){
        
    }
    
    const std::string& Rtti::GetName() const{
        return mName;
    }
    
    bool Rtti::IsInstanceOf(const Rtti& type) const{
        const Rtti* search = this;
        
        while(search){
            if(&type == search)
                return true;
            search = search->mBaseType;
        }
        
        return false;
    }

    bool Rtti::IsType(const Rtti& type) const{
        return this == &type;
    }
    
    std::ostream& operator<< (std::ostream& stream, const Rtti& o){
        stream << "Rtti[" << o.mName << "]";
        return stream;
    }
}
