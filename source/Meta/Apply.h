#ifndef APPLY_H_
#define APPLY_H_

#include "Variable.h"
#include "../DataTypes.h"
#include "Cast.h"

namespace bde {
    //
    // Functions that return values
    //

    template<typename Ret>
    void Apply(Ret (*fun)(), Variable &ret, const Variable *args, const U32 &argsCount) {
        Ret t;
        t = ((Ret (*) ())fun)();
        ret.type->Cast( ret.address, &t, GetMetaType(t) );
    }

    template<typename Ret, typename Arg0>
    void Apply(Ret (*fun)(Arg0), Variable &ret, const Variable *args, const U32 &argsCount) {
        Ret t;
        t = ((Ret (*) (Arg0)) fun)( Cast<Arg0>(args[0].address, *args[0].type) );
        ret.type->Cast( ret.address, &t, GetMetaType(t) );
    }

    template<typename Ret, typename Arg0, typename Arg1>
    void Apply(Ret (*fun)(Arg0, Arg1), Variable &ret, const Variable *args, const U32 &argsCount) {
        Ret t;
        t = ((Ret (*) (Arg0, Arg1)) fun)(Cast<Arg0>(args[0].address, *args[0].type),
                                         Cast<Arg1>(args[1].address, *args[1].type));
        ret.type->Cast( ret.address, &t, GetMetaType(t) );
    }

    //
    // Functions that don't return values
    //

    template<typename Arg0>
    void Apply(void (*fun)(Arg0), Variable &ret, const Variable *args, const U32 &argsCount) {
        ((void (*) (Arg0)) fun)( Cast<Arg0>(args[0].address, *args[0].type) );
    }

    template<typename Fun>
    void ApplyWrapper(void (*fun)(), Variable ret, Variable *args, U32 argCount) {
        Apply((Fun)fun, ret, args, argCount);
    };
    
} // namespace bde

#endif
