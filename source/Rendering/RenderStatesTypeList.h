#ifndef RENDER_STATES_TYPE_LIST_H_
#define RENDER_STATES_TYPE_LIST_H_

#include "StencilState.h"
#include "AlphaBlend.h"
#include "CullState.h"
#include "DepthBuffer.h"

namespace bde{
    struct RenderStatesTypeList{
        typedef TYPE_LIST((AlphaBlend, CullState, DepthBuffer, StencilState)) renderStateTypeList;
        
        static const U32 renderStatesCount = TypeListCount<renderStateTypeList>::value;
        
        template<typename T>
        static U32 IndexOfType(){
            return TypeListIndexOf<renderStateTypeList::head, T, renderStateTypeList::tail>::value;
        }
    };
}
	
#endif