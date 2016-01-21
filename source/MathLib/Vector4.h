#ifndef __BDEMath__Vector4__
#define __BDEMath__Vector4__

#include <iostream>
#include <glm/glm.hpp>
#include "MathLib.h"

namespace bde {
    template<typename R = float>
    class Vector4 : public VectorN<R,4>{
      public:
        /* ****************************
         * Construction & Destruction *
         * ***************************/
        Vector4(){
            
        }
        
        Vector4(const REAL &x, const REAL &y, const REAL &z, const REAL &w){
            VectorN<R, 4>::mComp[0] = x;
            VectorN<R, 4>::mComp[1] = y;
            VectorN<R, 4>::mComp[2] = z;
            VectorN<R, 4>::mComp[3] = w;
        }
        
        Vector4(const Vector4<R> &v){
            VectorN<R, 4>::mComp[0] = v.X();
            VectorN<R, 4>::mComp[1] = v.Y();
            VectorN<R, 4>::mComp[2] = v.Z();
            VectorN<R, 4>::mComp[3] = v.W();
        }
        
        Vector4(R *comp):VectorN<R, 4>(comp){
            
        }
        
        Vector4<R>& operator=(const Vector4<R> &v){
            if( this != &v ){
                VectorN<R, 4>::mComp[0] = v.X();
                VectorN<R, 4>::mComp[1] = v.Y();
                VectorN<R, 4>::mComp[2] = v.Z();
                VectorN<R, 4>::mComp[3] = v.W();
            }
            
            return *this;
        }

#if GLM_COMPATIBLE == 1
        Vector4(const glm::vec4 &v){
            VectorN<R, 4>::mComp[0] = v.x;
            VectorN<R, 4>::mComp[1] = v.y;
            VectorN<R, 4>::mComp[2] = v.z;
            VectorN<R, 4>::mComp[3] = v.w;
        }
        operator glm::vec4() const{
            return glm::vec4(X(),Y(),Z(),W());
        }
#endif

        /* *******************
         * Getters & Setters *
         * ******************/
        const R& X() const{
            return VectorN<R, 4>::mComp[0];
        }
        const R& Y() const{
            return VectorN<R, 4>::mComp[1];
        }
        const R& Z() const{
            return VectorN<R, 4>::mComp[2];
        }
        const R& W() const{
            return VectorN<R, 4>::mComp[3];
        }
        
        R& X(){
            return VectorN<R, 4>::mComp[0];
        }
        R& Y(){
            return VectorN<R, 4>::mComp[1];
        }
        R& Z(){
            return VectorN<R, 4>::mComp[2];
        }
        R& W(){
            return VectorN<R, 4>::mComp[3];
        }
    };
    
    using Vector4f = Vector4<float>;
    using Vector4d = Vector4<double>;

    /* ************************
     * Arithmentic Operations *
     * ***********************/
    template<typename R>
    Vector4<R> operator+(const Vector4<R> &v1, const Vector4<R> &v2){
        R comp[4];
        for(auto i=0; i<4; ++i){
            comp[i] = v1[i] + v2[i];
        }
        
        return Vector4<R>(comp);
    }
    
    template<typename R>
    Vector4<R> operator-(const Vector4<R> &v1, const Vector4<R> &v2){
        R comp[4];
        for(auto i=0; i<4; ++i){
            comp[i] = v1[i] - v2[i];
        }
        
        return Vector4<R>(comp);
    }
    
    template<typename R, typename S>
    Vector4<R> operator*(const Vector4<R> &v1, const S &f){
        R comp[4];
        for(auto i=0; i<4; ++i){
            comp[i] = v1[i] * f;
        }
        
        return Vector4<R>(comp);
    }
    
    template<typename R, typename S>
    Vector4<R> operator*(const S &f, const Vector4<R> &v1){
        R comp[4];
        for(auto i=0; i<4; ++i){
            comp[i] = f * v1[i];
        }
        
        return Vector4<R>(comp);
    }
    
    template<typename R, typename S>
    Vector4<R> operator/(const Vector4<R> &v1, const S &f){
        R comp[4];
        for(auto i=0; i<4; ++i){
            comp[i] = v1[i] / f;
        }
        
        return Vector4<R>(comp);
    }
    
    template<typename R, typename S>
    Vector4<R> operator/(const S &f, const Vector4<R> &v1){
        R comp[4];
        for(auto i=0; i<4; ++i){
            comp[i] = f / v1[i];
        }
        
        return Vector4<R>(comp);
    }
    
    /* *************
     * Comparisons *
     * ************/
    template<typename R>
    bool operator==(const Vector4<R> &v1, const Vector4<R> &v2){
        return std::memcmp((const R*)v1, (const R*)v2, 4*sizeof(R)) == 0;
    }
    
    template<typename R>
    bool operator!=(const Vector4<R> &v1, const Vector4<R> &v2){
        return !(v1 == v2);
    }
    
    template<typename R>
    std::ostream &operator<<(std::ostream &o, const Vector4<R> &v){
        o << "[ " << v.X() << ", " << v.Y() << ", " << v.Z() << ", " << v.W() << " ]";
        return o;
    }
} // namespace bde

#endif /* defined(__BDEMath__Vector4__) */
