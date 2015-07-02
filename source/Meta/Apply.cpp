//
//  Apply.cpp
//  BlackDogEngine
//
//  Created by Diego Jesus on 26/06/15.
//
//

#include "Apply.h"

namespace bde {
    template<>
    void Apply<void>(void (*fun)(), Variable &ret, const Variable *args, const U32 &argsCount) {
        fun();
    }
}