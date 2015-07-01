#include <iostream>

#include "../../source/Meta/MetaClass.h"
#include "../../source/Meta/Variable.h"

using namespace bde;

class A{
public:
    
    int val;
    
    int do_something(){
        std::cout << "in do_something() val was " << val << std::endl;
        return val*10;
    }
    
    float do_something_else(){
        return val-1;
    }
};

META_REGISTER_CLASS(A, MEMBER_FUNCTIONS(A, (
                                            MEMBER_FUNCTION(A, do_something),
                                            MEMBER_FUNCTION(A, do_something_else)
                                            )));

//bde::MetaClass gMetaClass_A("A", std::list<MetaMemberFunctionBase*>({
//    new MetaMemberFunction<A>("do_something", &A::do_something),
//    new MetaMemberFunction<A>("do_something_else", &A::do_something_else)
//}));


int main(int argc, char *argv[]){
    A a; a.val = 10;
    A c; c.val = 12;
    
    auto mlist = MEMBER_FUNCTIONS(A, (
                                      MEMBER_FUNCTION(A, do_something_else),
                                      MEMBER_FUNCTION(A, do_something)
                                      ));
    
    auto mf = gMetaClass_A.MemberFunctions().front();
    auto dse = gMetaClass_A.MemberFunctions().back();
    int b; Variable retVal(b);
    mf->ApplyToObject(&a, retVal, NULL, 0);
    std::cout << "in main b is: " << b << std::endl;
   
    mf->ApplyToObject(&c, retVal, NULL, 0);
    std::cout << "in main b is: " << b << std::endl;
    
    dse->ApplyToObject(&a, retVal, NULL, 0);
    std::cout << "in main b is: " << b << std::endl;
    
    dse->ApplyToObject(&c, retVal, NULL, 0);
    std::cout << "in main b is: " << b << std::endl;
    
    return 0;
}
