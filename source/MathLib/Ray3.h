//
//  Ray3.h
//  BDEMath
//
//  Created by Diego Jesus on 29/04/14.
//  Copyright (c) 2014 BlackDogEngine. All rights reserved.
//

#ifndef __BDEMath__Ray3__
#define __BDEMath__Ray3__

#include "MathLibConfigurations.h"

#include <iostream>
#include <CGAL/Cartesian.h>

#include "MathLib.h"
#include "Line3.h"

namespace bde {
    typedef CGAL::Cartesian<REAL>::K::Ray_3 Ray_3;

    class Ray3 {
      private:
        Ray_3 mRay;

      public:
        /* ****************************
         * Construction & Destruction *
         * ***************************/
        Ray3();
        Ray3(const Vector3<> &origin, const Vector3<> direction);
        Ray3(const Ray3 &r);

#if CGAL_COMPATIBLE == 1
        Ray3(const Ray_3 &ray);
        operator Ray_3() const;
#endif

        /* *******************
         * Getters & Setters *
         * ******************/
        Line3 SupportingLine() const;

        /* ************
         * Operations *
         * ***********/
        REAL SquaredDistance(const Ray3 &ray);
        REAL Distance(const Ray3 &ray);
        REAL SquaredDistance(const Vector3<> &v) const;
        REAL Distance(const Vector3<> &v) const;


        friend class Segment3;
    };
} // namespace bde
#else
namespace {
    class Ray3;
} // namespace bde
#endif /* defined(__BDEMath__Ray3__) */
