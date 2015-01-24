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

typedef CGAL::Cartesian<REAL>::Point_3 Point_3;
typedef CGAL::Cartesian<REAL>::Vector_3 Vector_3;
typedef CGAL::Cartesian<REAL>::Direction_3 Direction_3;

class Vector3{
private:
    glm::vec3 mVector;
public:
    /* ****************************
     * Construction & Destruction *
     * ***************************/
    Vector3();
    Vector3(const REAL &x, const REAL &y, const REAL &z);
    Vector3(const Vector3& v);
#if GLM_COMPATIBLE == 1
    Vector3(const glm::vec3 &v);
    operator glm::vec3() const;
#endif
#if CGAL_COMPATIBLE == 1
    Vector3(const Point_3 &p);
    Vector3(const Vector_3 &p);
    Vector3(const Direction_3 &p);
    operator Vector_3() const;
    operator Point_3() const;
    operator Direction_3() const;
#endif
    ~Vector3();
    
    /* *******************
     * Getters & Setters *
     * ******************/
    REAL X() const;
    REAL Y() const;
    REAL Z() const;

    REAL& X();
    REAL& Y();
    REAL& Z();

    REAL SquaredLength() const;
    REAL Length() const;
    
    /* ************
     * Operations *
     * ***********/
    Vector3 operator+(const Vector3 &v) const;
    Vector3 operator+=(const Vector3 &v);
    Vector3 operator-(const Vector3 &v) const;
    Vector3 operator-=(const Vector3 &v);
    Vector3 operator*(const REAL &f) const;
    friend Vector3 operator*(const REAL &f, const Vector3 &v);
    Vector3 operator/(const REAL &f);
    friend Vector3 operator/(const REAL &f, const Vector3 &v);
    Vector3 Cross(const Vector3 &v) const;
    REAL Dot(const Vector3 &v) const;
    REAL Normalize();
    
    bool IsColinear(const Vector3 &v) const;

    /* *************
     * Comparators *
     * ************/
    bool operator==(const Vector3 &v) const;
    bool operator!=(const Vector3 &v) const;
    
    friend std::ostream& operator<< (std::ostream &o, const Vector3 &v);
};

std::ostream& operator<< (std::ostream &o, const Vector3 &v);

#endif /* defined(__BDEMath__Vector3__) */
