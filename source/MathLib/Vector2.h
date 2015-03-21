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

namespace bde{
    typedef CGAL::Cartesian<REAL>::Point_2 Point_2;
    typedef CGAL::Cartesian<REAL>::Vector_2 Vector_2;
    typedef CGAL::Cartesian<REAL>::Direction_2 Direction_2;
    
    class Vector2{
    private:
        glm::vec2 mVector;
    public:
        /* ****************************
         * Construction & Destruction *
         * ***************************/
        Vector2();
        Vector2(const REAL &x, const REAL &y);
        Vector2(const Vector2& v);
        ~Vector2();
        
#if GLM_COMPATIBLE == 1
        Vector2(const glm::vec2 &v);
        operator glm::vec2() const;
#endif
#if CGAL_COMPATIBLE == 1
        Vector2(const Vector_2 &v);
        Vector2(const Point_2 &v);
        Vector2(const Direction_2 &v);
        
        operator Vector_2() const;
        operator Point_2() const;
        operator Direction_2() const;
#endif
        
        /* *******************
         * Getters & Setters *
         * ******************/
        const REAL& X() const;
        REAL& X();
        const REAL& Y() const;
        REAL& Y();
        
        REAL SquaredLength();
        REAL Length();
        
        /* ************
         * Operations *
         * ***********/
        Vector2 operator+(const Vector2 &v) const;
        Vector2 operator-(const Vector2 &v) const;
        Vector2 operator*(const REAL &f) const;
        friend Vector2 operator*(const REAL &f, const Vector2 &v);
        Vector2 operator/(const REAL &f) const;
        friend Vector2 operator/(const REAL &f, const Vector2 &v);
        REAL Dot(const Vector2 &v) const;
        
        /* *************
         * Comparisons *
         * ************/
        bool operator==(const Vector2 &v) const;
        bool operator!=(const Vector2 &v) const;
        
        friend std::ostream& operator<<(std::ostream &o, const Vector2 &v);
    };
} // namespace bde

#else
namespace bde{
    class Vector2;
} // namespace bde
#endif /* defined(__BDEMath__Vector2__) */
