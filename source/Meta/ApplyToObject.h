//
//  ApplyToObject.h
//  BlackDogEngine
//
//  Created by Diego Jesus on 22/06/15.
//
//

#ifndef BlackDogEngine_ApplyToObject_h
#define BlackDogEngine_ApplyToObject_h

namespace bde {
    struct ApplyToObject{
        //
        // Methods that return a value
        //
        template<typename RET, class C>
        static void Apply(C *object, RET (C::*fun)(), Variable ret, Variable *arguments, int numArguments){
            RET t;
            
            t = (object->*fun)();
            
            ret.type->Cast(ret.address, &t, GetMetaType(t));
        }
        
        //
        // Methods that don't return values
        //
        template<class C>
        static void Apply(C *object, void (C::*fun)(), Variable ret, Variable *arguments, int numArguments){
            (object->*fun)();
        }
    };
}

#endif
