#ifndef BlackDogEngine_GOComponentTypeList_h
#define BlackDogEngine_GOComponentTypeList_h

#include "Meta/TypeList.h"

#include "TransformComponent.h"

namespace bde {
    struct GOComponentTypeList{
        typedef TYPE_LIST((TransformComponent)) gocTypeList;
        
        static const U32 componentCount = TypeListCount<gocTypeList>::value;
        
        template<typename T>
        static U32 IndexOfType(){
            return TypeListIndexOf<gocTypeList::head, T, gocTypeList::tail>::value;
        }
    };
}

#endif
