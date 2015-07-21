#include "GetMetaTypeByType.h"

namespace bde {
    template<>
    const MetaType &GetMetaTypeByType<void>() {
        return GetMetaType();
    }
}