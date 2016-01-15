//
//  Plane.h
//  BDEMath
//
//  Created by Diego Jesus on 29/04/14.
//  Copyright (c) 2014 BlackDogEngine. All rights reserved.
//

#ifndef __BDEMath__Plane__
#define __BDEMath__Plane__

#include <iostream>
#include <CGAL/Cartesian.h>

#include "Vector3.h"
#include "Line3.h"
#include "Ray3.h"
#include "Segment3.h"

namespace bde {
    typedef CGAL::Cartesian<REAL>::Plane_3 Plane_3;

    struct PlaneIntersection {
        enum {
            NoIntersection,
            PointIntersection,
            LineIntersection,
            Coplanar
        } intersectionType;
        Vector3<> intersectionPoint;
        Line3 intersectionLine;
    };

    class Plane {
      private:
        Plane_3 mPlane;

      public:
        /* ****************************
         * Construction & Destruction *
         * ***************************/
        Plane();
        Plane(const Vector3<> &point, const Vector3<> &normal);
        Plane(const Vector3<> &p1, const Vector3<> &p2, const Vector3<> &p3);
        Plane(const Line3 &line, const Vector3<> point);
        ~Plane();

        /* *******************
         * Getters & Setters *
         * ******************/
        Vector3<> Normal() const;
        /**
         * Returns a vector orthogonal to the normal vector.
         */
        Vector3<> Base() const;
        /**
         * Returns a vector that is orthogonal to both the normal and Base1 vectors.
         */
        Vector3<> Base2() const;

        /* ************
         * Operations *
         * ***********/
        PlaneIntersection Intersection(const Plane &other);
        PlaneIntersection Intersection(const Line3 &line);
        PlaneIntersection Intersection(const Ray3 &ray);

        Vector3<> Project(const Vector3<> &v);
        REAL DistanceToPoint(const Vector3<> &v);

        bool Contained(const Vector3<> &v);
        bool Contained(const Segment3 &v);
    };
} // namespace bde

#else

namespace bde {
    class Plane;
} // namespace bde

#endif /* defined(__BDEMath__Plane__) */
