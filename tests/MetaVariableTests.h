#ifndef METAVARIABLETESTS_H_
#define METAVARIABLETESTS_H_

#include <iostream>

#include <cpptest.h>

#include "../source/Meta/MetaVariable.h"

int a=10;
char* s="some string";
int b=50;

META_REGISTER_VAR(a);
META_REGISTER_VAR(s);
META_REGISTER_VAR(b);

class MetaVariableTests : public Test::Suite{
    public:
        MetaVariableTests(){
            TEST_ADD( MetaVariableTests::MetaVariableTests_MetaVariablesExist_MetaVariablesCorrec );
            TEST_ADD( MetaVariableTests::MetaVariableTests_AutoListerCorrect );
        }

    private:

        void MetaVariableTests_MetaVariablesExist_MetaVariablesCorrec(){
            TEST_ASSERT( gMetaVariable_a.name=="a" );
            TEST_ASSERT( gMetaVariable_a.address==&a );

            TEST_ASSERT( gMetaVariable_s.name=="s" );
            TEST_ASSERT( gMetaVariable_s.address==&s );
        }

        void MetaVariableTests_AutoListerCorrect(){
            auto autoListEl = bde::AutoLister<bde::MetaVariable>::Head();

            bde::MetaVariable* var = (bde::MetaVariable*)autoListEl;
            TEST_ASSERT( var->name == "b" );
            autoListEl = autoListEl->Next();

            var = (bde::MetaVariable*)autoListEl;
            TEST_ASSERT( var->name == "s" );
            autoListEl = autoListEl->Next();

            var = (bde::MetaVariable*)autoListEl;
            TEST_ASSERT( var->name == "a" );
            autoListEl = autoListEl->Next();

            TEST_ASSERT( autoListEl == NULL );
        }
}; 
#endif
