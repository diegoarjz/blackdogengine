//
//  Vector2.h
//  BDEMath
//
//  Created by Diego Jesus on 29/04/14.
//  Copyright (c) 2014 BlackDogEngine. All rights reserved.
//

#ifndef __BDEMath__Vector2__
#define __BDEMath__Vector2__

#include "MathLibConfigurations.h"

#include <iostream>
#include <glm/glm.hpp>
#include <CGAL/Cartesian.h>

#include "VectorN.h"

namespace bde {
    typedef CGAL::Cartesian<REAL>::Point_2 Point_2;
    typedef CGAL::Cartesian<REAL>::Vector_2 Vector_2;
    typedef CGAL::Cartesian<REAL>::Direction_2 Direction_2;

    template<typename R=float>
    class Vector2 : public VectorN<R,2>{
      public:
        /* ****************************
         * Construction & Destruction *
         * ***************************/
        Vector2(){
            
        }
        
        Vector2(const R &x, const R &y){
            VectorN<R,2>::mComp[0] = x;
            VectorN<R,2>::mComp[1] = y;
        }
        
        Vector2(const Vector2 &v){
            VectorN<R,2>::mComp[0] = v.X();
            VectorN<R,2>::mComp[1] = v.Y();
        }
        
        Vector2(R *comp):VectorN<R, 2>(comp){
        
        }

        Vector2<R>& operator=(const Vector2<R> &lhs){
            if( this != &lhs ){
                VectorN<R,2>::mComp[0] = lhs.X();
                VectorN<R,2>::mComp[1] = lhs.Y();
            }
            
            return *this;
        }

#if GLM_COMPATIBLE == 1
        Vector2(const glm::vec2 &v) {
            VectorN<R,2>::mComp[0] = v.x;
            VectorN<R,2>::mComp[1] = v.y;
        }
        
        operator glm::vec2() const {
            return glm::vec2(X(), Y());
        }
#endif
#if CGAL_COMPATIBLE == 1
        Vector2(const Vector_2 &v) {
            VectorN<R,2>::mComp[0] = v.x();
            VectorN<R,2>::mComp[1] = v.y();
        }
        
        Vector2(const Point_2 &v) {
            VectorN<R,2>::mComp[0] = v.x();
            VectorN<R,2>::mComp[1] = v.y();
        }
        
        Vector2(const Direction_2 &v) {
            VectorN<R,2>::mComp[0] = v.dx();
            VectorN<R,2>::mComp[1] = v.dy();
        }
        
        operator Vector_2() const {
            return Vector_2(X(), Y());
        }
        
        operator Point_2() const {
            return Point_2(X(), Y());
        }
        
        operator Direction_2() const {
            return Direction_2(X(), Y());
        }
#endif

        /* *******************
         * Getters & Setters *
         * ******************/
        const REAL &X() const{
            return (*this)[0];
        }
        REAL &X(){
            return (*this)[0];
        }
        const REAL &Y() const{
            return (*this)[1];
        }
        REAL &Y(){
            return (*this)[1];
        }
    };
    
    using Vector2f = Vector2<float>;
    
    /* ************
     * Operations *
     * ***********/
    template<typename R>
    Vector2<R> operator+(const Vector2<R> &v1, const Vector2<R> &v2){
        R comp[2];
        for(auto i=0; i<2; ++i){
            comp[i] = v1[i] + v2[i];
        }
        
        return Vector2<R>(comp);
    }
    
    template<typename R>
    Vector2<R> operator-(const Vector2<R> &v1, const Vector2<R> &v2){
        R comp[2];
        for(auto i=0; i<2; ++i){
            comp[i] = v1[i] - v2[i];
        }
        
        return Vector2<R>(comp);
    }
    
    template<typename R, typename S>
    Vector2<R> operator*(const Vector2<R> &v1, const S &f){
        R comp[2];
        for(auto i=0; i<2; ++i){
            comp[i] = v1[i] *f;
        }
        
        return Vector2<R>(comp);
    }
    
    template<typename R, typename S>
    Vector2<R> operator*(const S &f, const Vector2<R> &v1){
        R comp[2];
        for(auto i=0; i<2; ++i){
            comp[i] = f * v1[i];
        }
        
        return Vector2<R>(comp);
    }
    
    template<typename R, typename S>
    Vector2<R> operator/(const Vector2<R> &v1, const S &f){
        R comp[2];
        for(auto i=0; i<2; ++i){
            comp[i] = v1[i] / f;
        }
        
        return Vector2<R>(comp);
    }
    
    template<typename R, typename S>
    Vector2<R> operator/(const S &f, const Vector2<R> &v1){
        R comp[2];
        for(auto i=0; i<2; ++i){
            comp[i] = f / v1[i];
        }
        
        return Vector2<R>(comp);
    }
    
    /* *************
     * Comparisons *
     * ************/
    template<typename R>
    bool operator==(const Vector2<R> &v1, const Vector2<R> &v2){
        return std::memcmp((const R*)v1, (const R*)v2, 2*sizeof(R)) == 0;
    }
    
    template<typename R>
    bool operator!=(const Vector2<R> &v1, const Vector2<R> &v2){
        return !(v1 == v2);
    }
    
    template<typename R>
    std::ostream &operator<<(std::ostream &o, const Vector2<R> &v){
        o << "[ " << v.X() << ", " << v.Y() << " ]";
        return o;
    }
} // namespace bde

#endif /* defined(__BDEMath__Vector2__) */
