#ifndef __BlackDogEngine__Cast__
#define __BlackDogEngine__Cast__

#include "MetaType.h"

namespace bde {
    //
    // Cast function
    //
    template<typename To>
    To Cast(const void *v, const MetaType &type) {
        To t;
        GetMetaType(t).Cast(&t, v, type);
        return t;
    }
    
}
#endif /* defined(__BlackDogEngine__Cast__) */
