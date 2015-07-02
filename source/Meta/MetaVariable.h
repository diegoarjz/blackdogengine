#ifndef METAVARIABLE_H_
#define METAVARIABLE_H_

#include "MetaType.h"
#include "AutoLister.h"
#include "../DataTypes.h"

namespace bde {

#define META_REGISTER_VAR(v)\
    bde::MetaVariable gMetaVariable_##v(#v, &v, __FILE__, __LINE__)

    /**
     * Holds meta-information about a global variable.
     */
    struct MetaVariable : public AutoLister<MetaVariable> {
        template<typename Var>
        MetaVariable(const char *name_, Var *var, const char *file, U32 line)
            : name(name_)
            , address(var)
            , type(GetMetaType(*var))
            , fileName(file)
            , lineNumber(line) {
        }

        const char *const name;
        void *const address;
        const MetaType &type;
        const char *const fileName;
        const U32 lineNumber;
    }; // struct MetaVariable

    /**
     * Prints a Meta Variable to std::cout.
     */
    void PrintMetaVariable(const MetaVariable &var);

    /**
     * Prints all meta variables to std::cout
     */
    void PrintAllMetaVariables();

} // namespace bde
#endif
