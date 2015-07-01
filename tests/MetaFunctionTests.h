#ifndef METAFUNCTIONTESTS_H_
#define METAFUNCTIONTESTS_H_

#include <iostream>
#include <cpptest.h>

#include "../source/Meta/FunctionSignature.h"

int foo(int){return 0;}

class MetaFunctionTests : public Test::Suite{
    public:
        MetaFunctionTests(){
            TEST_ADD( MetaFunctionTests::MetaFunctionTests_TestFunctionSignature );
        }
    private:
        void MetaFunctionTests_TestFunctionSignature(){
            bde::FunctionSignature sig(foo);

            TEST_ASSERT( sig.ReturnType()->Name() == "int" );
            TEST_ASSERT( sig.ArgumentsCount() == 1 );
            TEST_ASSERT( sig.ArgumentType(0)->Name() == "int" );
        }
};

#endif
