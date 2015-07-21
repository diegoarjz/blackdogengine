#ifndef BlackDogEngine_TypeList_h
#define BlackDogEngine_TypeList_h

#include "../DataTypes.h"
#include "If.h"

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
    
    // Type List Count
    template<typename TYPE_LIST>
    struct TypeListCount{
        enum{ value = 1 + TypeListCount<typename TYPE_LIST::tail>::value };
    };
    
    template<>
    struct TypeListCount<NullTypeList>{
        enum{ value = 0 };
    };
    
    // Type List Index Of
    template<typename X, typename Y>
    struct SameType{
        enum{ result = 0 }; // They're not of the same type
    };
    
    template<typename T>
    struct SameType<T,T>{
        enum{ result = 1 }; // They are of the same type.
    };
    
    template<typename Head, typename type, typename Tail>
    struct TypeListIndexOf{
        enum{ value = 1 + TypeListIndexOf<typename Tail::head, type, typename Tail::tail>::value };
    };
    
    template<typename T, typename tail>
    struct TypeListIndexOf<T, T, tail>{
        enum{ value = 0 };
    };
    
#define TYPE_LIST(A) bde::cons<void (*)A>::type
} // namespace bde

#endif
