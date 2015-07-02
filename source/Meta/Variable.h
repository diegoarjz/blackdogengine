#ifndef VARIABLE_H_
#define VARIABLE_H_

#include "MetaType.h"

namespace bde {

    struct Variable {
        Variable() : address(0), type( &GetMetaType() ) {}

        template<typename T>
        Variable(const T &t) : address((void *)&t), type(&GetMetaType(t)) {}

        void *address;
        const MetaType *type;
    }; // struct Variable
    
} // namespace bde

#else

#endif
