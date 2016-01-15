//
//  Vector3.h
//  BDEMath
//
//  Created by Diego Jesus on 29/04/14.
//  Copyright (c) 2014 BlackDogEngine. All rights reserved.
//

#ifndef __BDEMath__Vector3__
#define __BDEMath__Vector3__

#include "MathLibConfigurations.h"

#include <iostream>
#include <CGAL/Cartesian.h>
#include <glm/glm.hpp>

#include "VectorN.h"

namespace bde {
    typedef CGAL::Cartesian<REAL>::Point_3 Point_3;
    typedef CGAL::Cartesian<REAL>::Vector_3 Vector_3;
    typedef CGAL::Cartesian<REAL>::Direction_3 Direction_3;

    template<class R=float>
    class Vector3 : public VectorN<R,3>{
      private:

      public:
        /* ****************************
         * Construction & Destruction *
         * ***************************/
        Vector3(){
            
        };
        
        Vector3(const R &x, const R &y, const R &z){
            VectorN<R,3>::mComp[0] = x;
            VectorN<R,3>::mComp[1] = y;
            VectorN<R,3>::mComp[2] = z;
        }
        
        Vector3(const Vector3 &v){
            VectorN<R,3>::mComp[0] = v.X();
            VectorN<R,3>::mComp[1] = v.Y();
            VectorN<R,3>::mComp[2] = v.Z();
        }
        
        Vector3(R* comp):VectorN<R,3>(comp){
            
        }
        
        Vector3<R>& operator=(const Vector3<R> &lhs){
            if(this != &lhs){
                VectorN<R,3>::mComp[0] = lhs.X();
                VectorN<R,3>::mComp[1] = lhs.Y();
                VectorN<R,3>::mComp[2] = lhs.Z();
            }
            
            return *this;
        }
        
#if GLM_COMPATIBLE == 1
        Vector3(const glm::vec3 &v){
            VectorN<R,3>::mComp[0] = v.x;
            VectorN<R,3>::mComp[1] = v.y;
            VectorN<R,3>::mComp[2] = v.z;
        }
        operator glm::vec3() const{
            return glm::vec3(X(), Y(), Z());
        }
#endif
#if CGAL_COMPATIBLE == 1
        Vector3(const Point_3 &p){
            VectorN<R,3>::mComp[0] = p.x();
            VectorN<R,3>::mComp[1] = p.y();
            VectorN<R,3>::mComp[2] = p.z();
        }
        Vector3(const Vector_3 &p){
            VectorN<R,3>::mComp[0] = p.x();
            VectorN<R,3>::mComp[1] = p.y();
            VectorN<R,3>::mComp[2] = p.z();
        }
        Vector3(const Direction_3 &p){
            VectorN<R,3>::mComp[0] = p.dx();
            VectorN<R,3>::mComp[1] = p.dy();
            VectorN<R,3>::mComp[2] = p.dz();
        }
        operator Vector_3() const{
            return Vector3_(X(), Y(), Z());
        }
        operator Point_3() const{
            return Point_3(X(), Y(), Z());
        }
        operator Direction_3() const{
            return Direction_(X(), Y(), Z());
        }
#endif

        /* *******************
         * Getters & Setters *
         * ******************/
        const R& X() const{
            return (*this)[0];
        }
        const R& Y() const{
            return (*this)[1];
        }
        const R& Z() const{
            return (*this)[2];
        }

        R &X(){
            return (*this)[0];
        }
        R &Y(){
            return (*this)[1];
        }
        R &Z(){
            return (*this)[2];
        }

        Vector3<R> Cross(const Vector3 &v) const{
//            return Vector3( glm::cross(mVector, v.mVector) );
            return Vector3<R>(Y()*v.Z()-Z()*v.Y(),
                              Z()*v.X()-X()*v.Z(),
                              X()*v.Y()-Y()*v.X());
        }
    };
    
    using Vector3f = Vector3<float>;
    using Vector3d = Vector3<double>;
    
    /* ************************
     * Arithmentic Operations *
     * ***********************/
    template<typename R>
    Vector3<R> operator+(const Vector3<R> &v1, const Vector3<R> &v2){
        R comp[3];
        for(auto i=0; i<3; ++i){
            comp[i] = v1[i] + v2[i];
        }
        
        return Vector3<R>(comp);
    }
    
    template<typename R>
    Vector3<R> operator-(const Vector3<R> &v1, const Vector3<R> &v2){
        R comp[3];
        for(auto i=0; i<3; ++i){
            comp[i] = v1[i] - v2[i];
        }
        
        return Vector3<R>(comp);
    }
    
    template<typename R, typename S>
    Vector3<R> operator*(const Vector3<R> &v1, const S &f){
        R comp[3];
        for(auto i=0; i<3; ++i){
            comp[i] = v1[i] *f;
        }
        
        return Vector3<R>(comp);
    }
    
    template<typename R, typename S>
    Vector3<R> operator*(const S &f, const Vector3<R> &v1){
        R comp[3];
        for(auto i=0; i<3; ++i){
            comp[i] = f * v1[i];
        }
        
        return Vector3<R>(comp);
    }
    
    template<typename R, typename S>
    Vector3<R> operator/(const Vector3<R> &v1, const S &f){
        R comp[3];
        for(auto i=0; i<3; ++i){
            comp[i] = v1[i] / f;
        }
        
        return Vector3<R>(comp);
    }
    
    template<typename R, typename S>
    Vector3<R> operator/(const S &f, const Vector3<R> &v1){
        R comp[3];
        for(auto i=0; i<3; ++i){
            comp[i] = f / v1[i];
        }
        
        return Vector3<R>(comp);
    }
    
    /* *************
     * Comparisons *
     * ************/
    template<typename R>
    bool operator==(const Vector3<R> &v1, const Vector3<R> &v2){
        return std::memcmp((const R*)v1, (const R*)v2, 3*sizeof(R)) == 0;
    }
    
    template<typename R>
    bool operator!=(const Vector3<R> &v1, const Vector3<R> &v2){
        return !(v1 == v2);
    }

    template<typename R>
    std::ostream &operator<< (std::ostream &o, const Vector3<R> &v){
        o << "[ " << v.X() << ", " << v.Y() << ", " << v.Z() << " ]";
        return o;
    }

} // namespace bde

#endif /* defined(__BDEMath__Vector3__) */
