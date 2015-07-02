//
//  MetaClass.h
//  BlackDogEngine
//
//  Created by Diego Jesus on 19/06/15.
//
//

#ifndef __BlackDogEngine__MetaClass__
#define __BlackDogEngine__MetaClass__

#include <stdio.h>
#include <list>

#include "AutoLister.h"
#include "MetaMemberFunction.h"

namespace bde {

#define META_REGISTER_CLASS(CLASS, M_FUNCTIONS) \
    bde::MetaClass gMetaClass_##CLASS(#CLASS, M_FUNCTIONS)
    
#define MEMBER_FUNCTIONS(CLASS, FunctionList) std::list<MetaMemberFunctionBase*>({FunctionList})
    
#define MEMBER_FUNCTION(CLASS, Function) new MetaMemberFunction<CLASS>(#Function, &CLASS::Function)
    
    class MetaClass : public AutoLister<MetaClass>{
    private:
        const char * mName;
        
        // super class
        // sub classes
        // data members
        // member functions
        std::list<MetaMemberFunctionBase*> mMemberFunctions;
    public:
        
        MetaClass(const char* name, std::list<MetaMemberFunctionBase*> memberFuctions){
            mName = name;
            mMemberFunctions = memberFuctions;
        }
        
        ~MetaClass(){
            for(auto l : mMemberFunctions){
                delete l;
            }
            mMemberFunctions.clear();
        }
        
        const char* Name() const{
            return mName;
        }
        
        const std::list<MetaMemberFunctionBase*>& MemberFunctions() const{
            return mMemberFunctions;
        }
    };
    
//    template<class C>
//    void PrintMetaClass(const MetaClass<C>& mc){
//        std::cout << "class " << mc.Name() << std::endl;
//        for (auto memberFunction : mc.MemberFunctions()) {
//            std::cout << "  " << memberFunction.Name() << std::endl;
//        }
//    }

//    void PrintAllMetaClasses();
}

#endif /* defined(__BlackDogEngine__MetaClass__) */
