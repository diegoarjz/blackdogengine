#ifndef BlackDogEngine_If_h
#define BlackDogEngine_If_h

namespace bde{
    
    template<bool condition, typename TrueResult, typename FalseResult>
    struct IF;
    
    template<typename TrueResult, typename FalseResult>
    struct IF<true, TrueResult, FalseResult>{
        typedef TrueResult result;
    };
    
    template<typename TrueResult, typename FalseResult>
    struct IF<false, TrueResult, FalseResult>{
        typedef FalseResult result;
    };
    
} // namespace bde

#endif
