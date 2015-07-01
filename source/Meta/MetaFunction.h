#ifndef METAFUNCTION_H_
#define METAFUNCTION_H_

#include "AutoLister.h"
#include "FunctionSignature.h"
#include "Variable.h"
#include "Apply.h"

namespace bde {
    /**
     * Encapsulates meta-information about a function.
     *
     * Provides methods to call the function with arguments.
     */
    class MetaFunction : public AutoLister<MetaFunction> {
      private:
        const char *mName;
        FunctionSignature mSignature;
        void (* mFunction) ();
        void (* mApplyWrapper) (void (*fun)(), Variable, Variable *, U32);
    public:

        template<typename Fun>
        MetaFunction(const char *name, Fun fun)
            :mName(name)
            ,mSignature(fun)
            ,mFunction((void(*)())fun)
            ,mApplyWrapper(ApplyWrapper<Fun>) {
        }

        const char *Name() const;
        const MetaType *ReturnType() const;
        const MetaType *ArgumentType(U32 index) const;
        U32 ArgumentsCount() const;
        const FunctionSignature& FunctionSignature() const;
        
        void Apply(Variable ret, Variable *args, U32 argsCount ) const;
    }; // class MetaFunction

    /**
     * Prints a meta function to std::cout
     */
    void PrintMetaFunction(MetaFunction mf);
    
    /**
     * Prints all meta functions to std::cout.
     */
    void PrintAllMetaFunctions();

#define META_REGISTER_FUN(f)\
bde::MetaFunction gMetaFunction_##f(#f, f)
} // namespce bde

#else
namespace bde{
    class MetaFunction;;
} // namespace bde
#endif
