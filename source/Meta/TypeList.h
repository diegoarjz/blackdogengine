//
//  TypeList.h
//  BlackDogEngine
//
//  Created by Diego Jesus on 22/06/15.
//
//

#ifndef BlackDogEngine_TypeList_h
#define BlackDogEngine_TypeList_h

namespace bde{
    
    template<typename H, typename T>
    struct TypeList{
        typedef H head;
        typedef T tail;
    };
    
    struct NullTypeList{};
    
    template <class Fun> struct cons;
    
    template <typename T0>
    struct cons<void (*)(T0)>{
        typedef TypeList<T0, NullTypeList> type;
    };
    
    template <typename T0, typename T1>
    struct cons<void (*)(T0, T1)>{
        typedef TypeList<T0, TypeList<T1, NullTypeList>> type;
    };
    
    template <typename T0, typename T1, typename T2>
    struct cons<void (*)(T0, T1, T2)>{
        typedef TypeList<T0, TypeList<T1, TypeList<T2, NullTypeList>>> type;
    };
    
    template <typename T0, typename T1, typename T2, typename T3>
    struct cons<void (*)(T0, T1, T2, T3)>{
        typedef TypeList<T0, TypeList<T1, TypeList<T2, TypeList<T3, NullTypeList>>>> type;
    };
    
#define TYPE_LIST(A) bde::cons<void (*)A>::type
} // namespace bde

#endif
