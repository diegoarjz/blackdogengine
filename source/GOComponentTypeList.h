#ifndef BlackDogEngine_GOComponentTypeList_h
#define BlackDogEngine_GOComponentTypeList_h

#include "meta/TypeList.h"

#include "TransformComponent.h"
#include "Camera.h"

namespace bde {
    struct GOComponentTypeList{
        typedef TYPE_LIST((TransformComponent, Camera)) gocTypeList;
        
        static const U32 componentCount = TypeListCount<gocTypeList>::value;
        
        template<typename T>
        static U32 IndexOfType(){
            return TypeListIndexOf<gocTypeList::head, T, gocTypeList::tail>::value;
        }
    };
}

#endif
