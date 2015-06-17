//
//  Vector4.h
//  BDEMath
//
//  Created by Diego Jesus on 29/04/14.
//  Copyright (c) 2014 BlackDogEngine. All rights reserved.
//

#ifndef __BDEMath__Vector4__
#define __BDEMath__Vector4__

#include <iostream>
#include <glm/glm.hpp>
#include "MathLib.h"
#include "Matrix4.h"

namespace bde {
    class Vector4 {
      private:
        glm::vec4 mVector;
      public:
        /* ****************************
         * Construction & Destruction *
         * ***************************/
        Vector4();
        Vector4(const REAL &x, const REAL &y, const REAL &z, const REAL &w);
        Vector4(const Vector4 &v);
        ~Vector4();

#if GLM_COMPATIBLE == 1
        Vector4(const glm::vec4 &v);
        operator glm::vec4() const;
#endif

        /* *******************
         * Getters & Setters *
         * ******************/
        REAL X() const;
        REAL Y() const;
        REAL Z() const;
        REAL W() const;

        REAL SquaredLength() const;
        REAL Length() const;

        /* ************
         * Operations *
         * ***********/
        Vector4 operator+(const Vector4 &v) const;
        Vector4 operator+=(const Vector4 &v);
        Vector4 operator-(const Vector4 &v) const;
        Vector4 operator-=(const Vector4 &v);
        friend Vector4 operator*(const REAL &s, const Vector4 &v);
        Vector4 operator*(const REAL &s);
        Vector4 operator*(const Matrix4 &m);
        REAL Normalize();

        friend std::ostream &operator<< (std::ostream &o, const Vector4 &v);
    };

    std::ostream &operator<< (std::ostream &o, const Vector4 &v);
} // namespace bde

#else

namespace bde {
    class Vector4;
} // namespace bde
#endif /* defined(__BDEMath__Vector4__) */
