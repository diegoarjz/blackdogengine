
#include "NumericMetaType.h"

namespace bde{
    
#define NUMERIC_DATA_TYPE_NAME( TYPE ) \
    template<>\
    const char* NumericMetaType<TYPE>::Name() const{ \
        return #TYPE; \
    } \

    NUMERIC_DATA_TYPE_NAME(I16);
    NUMERIC_DATA_TYPE_NAME(U16);
    
    NUMERIC_DATA_TYPE_NAME(I32);
    NUMERIC_DATA_TYPE_NAME(U32);
    
    NUMERIC_DATA_TYPE_NAME(I64);
    NUMERIC_DATA_TYPE_NAME(U64);
    
    NUMERIC_DATA_TYPE_NAME(F32);
    NUMERIC_DATA_TYPE_NAME(F64);
    
}