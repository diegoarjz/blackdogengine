#ifndef FUNCTIONSIGNATURE_H_
#define FUNCTIONSIGNATURE_H_

#include "../DataTypes.h"
#include "MetaType.h"

namespace bde {
    
    /**
     * Provides information on a function signature, namely its return
     * and parameter types and count.
     *
     * Has a set of templated constructors taking function pointers and 
     * automatically define the return and argument types and count.
     *
     * Example:
     * float mul(float a, float b) {...}
     * FunctionSignature fs(mul);
     */
    class FunctionSignature {
      private:
        const MetaType *mReturnType;
        const MetaType **mArgumentsType;
        U32 mArgumentsCount;

      public:
        /* ****************************
         * Construction & Destruction *
         * ***************************/
        template<typename Ret>
        FunctionSignature(Ret (*) ());

        template<typename Ret, typename Arg0>
        FunctionSignature(Ret (*)(Arg0));

        template<typename Ret, typename Arg0, typename Arg1>
        FunctionSignature(Ret (*)(Arg0, Arg1));
        
        template<typename Ret, typename Arg0, typename Arg1, typename Arg2>
        FunctionSignature(Ret (*)(Arg0, Arg1, Arg2));
        
        template<typename Ret, typename Arg0, typename Arg1, typename Arg2, typename Arg3>
        FunctionSignature(Ret (*)(Arg0, Arg1, Arg2, Arg3));
        
        template<typename Ret, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
        FunctionSignature(Ret (*)(Arg0, Arg1, Arg2, Arg3, Arg4));
        
        template<typename Ret, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5>
        FunctionSignature(Ret (*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5));
        
        template<typename Ret, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6>
        FunctionSignature(Ret (*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6));
        
        template<typename Ret, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7>
        FunctionSignature(Ret (*)(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7));

        /* *******************
         * Getters & Setters *
         * ******************/
        const MetaType *ReturnType() const;
        const MetaType *ArgumentType(const int &index) const;
        U32 ArgumentsCount() const;
    }; // class FunctionSignature

    template<typename Ret>
    FunctionSignature::FunctionSignature(Ret (*) ()) {
        mReturnType = &GetMetaTypeByType<Ret>();
        mArgumentsType = 0;
        mArgumentsCount = 0;
    }
    
    template<typename Ret, typename Arg0>
    FunctionSignature::FunctionSignature(Ret (*)(Arg0)) {
        mReturnType = &GetMetaTypeByType<Ret>();
        static const MetaType *args[] = { &GetMetaTypeByType<Arg0>() };
        mArgumentsType = args;
        mArgumentsCount = 1;
    }
    
    template<typename Ret, typename Arg0, typename Arg1>
    FunctionSignature::FunctionSignature(Ret (*)(Arg0, Arg1)) {
        mReturnType = &GetMetaTypeByType<Ret>();
        static const MetaType *args[] = {
            &GetMetaTypeByType<Arg0>(),
            &GetMetaTypeByType<Arg1>()
        };
        mArgumentsType = args;
        mArgumentsCount = 2;
    }
    
    /**
     * Prints a function signature to std::cout.
     *
     * @parameter fs    The function signature.
     * @parameter name  An optional function name.
     */
    void PrintFunctionSignature(const FunctionSignature &fs, const std::string &name = "");
} // namespace bde
#endif
