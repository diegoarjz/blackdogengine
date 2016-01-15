//
//  VectorN.h
//  BlackDogEngine
//
//  Created by Diego  Jesus on 06/01/16.
//
//

#ifndef VectorN_h
#define VectorN_h

#include <cstring>

#include "../DataTypes.h"

namespace bde {
    template<typename R, int N>
    class VectorN{
    protected:
        R mComp[N];
    public:
        using comp_t = R;
        static const int num_comp = N;
        
        VectorN(){
            for(auto i=0; i<N; ++i){
                mComp[i] = 0;
            }
        }
        
        VectorN(R *comp){
            for(auto i=0; i<N; ++i){
                mComp[i] = comp[i];
            }
        }
        
        operator R*(){
            return mComp;
        }
        
        operator const R*() const{
            return mComp;
        }
        
        const R& operator[](const U32 &n) const{
            return mComp[n];
        }
        
        R& operator[](const U32 &n){
            return mComp[n];
        }
        
        R SquaredLength() const{
            R sum(0);
            for(auto i=0; i<N; ++i){
                sum += mComp[i]*mComp[i];
            }
            return sum;
        }
        
        R Length() const{
            return std::sqrt( SquaredLength() );
        }
        
        R Normalize(){
            auto len = Length();
            auto invLen = 1/len;
            
            for(auto i=0; i<N; ++i){
                mComp[i] *= invLen;
            }
            
            return len;
        }
        
        R Dot(const VectorN<R,N> &rhs) const{
            R sum(0);
            for(auto i=0; i<N; ++i){
                sum += mComp[i]*rhs.mComp[i];
            }
            return sum;
        }
    }; // class VectorN
    
} // namespace bde

#endif /* VectorN_h */
