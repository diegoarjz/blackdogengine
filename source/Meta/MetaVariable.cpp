//
//  MetaVariable.cpp
//  BlackDogEngine
//
//  Created by Diego Jesus on 19/06/15.
//
//

#include "MetaVariable.h"

namespace bde{
    
    void PrintMetaVariable(const MetaVariable &var) {
        std::cout << "Var " << var.type.Name() << " " << var.name << " @ " << var.address << std::endl;
    }
    
    void PrintAllMetaVariables() {
        auto mv = MetaVariable::Head();
        
        // Iterate over the list of variables
        while(mv != NULL) {
            PrintMetaVariable( *mv );
            mv = mv->Next();
        }
    }
}