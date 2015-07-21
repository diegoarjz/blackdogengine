#ifndef BlackDogEngine_GetMetaTypeByType_h
#define BlackDogEngine_GetMetaTypeByType_h

#include "MetaType.h"

namespace bde {
    template<typename T>
    const MetaType &GetMetaTypeByType() {
        T t;
        return GetMetaType(t);
    }
    template<>
    const MetaType &GetMetaTypeByType<void>();
} // namespace bde;

#endif
