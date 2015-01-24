//
//  Line3.h
//  BDEMath
//
//  Created by Diego Jesus on 29/04/14.
//  Copyright (c) 2014 BlackDogEngine. All rights reserved.
//

#ifndef __BDEMathlib__Line3__
#define __BDEMathlib__Line3__

#include "MathLibConfigurations.h"

#include <iostream>
#include <CGAL/Cartesian.h>
#include "Vector3.h"

typedef CGAL::Cartesian<REAL>::Line_3 Line_3;

class Line3{
private:
    Line_3 mLine;
public:
    /* ****************************
     * Construction & Destruction *
     * ***************************/
    Line3();
    Line3(const ::Vector3 &origin, const ::Vector3 &direction);
    Line3(const Line3 &line);
    ~Line3();
    
#if CGAL_COMPATIBLE == 1
    Line3(const Line_3 &line);
    operator Line_3() const;
#endif
    
    /* *******************
     * Getters & Setters *
     * ******************/
    ::Vector3 Point() const;
    ::Vector3 Vector() const;

    
    /* ************
     * Operations *
     * ***********/
    REAL SquaredDistance(const Line3 &line) const;
    REAL Distance(const Line3 &line) const;
    REAL SquaredDistance(const Vector3 &point) const;
    REAL Distance(const Vector3 &point) const;
    
    Vector3 Projection(const Vector3 &point) const;
    
    /**
     * Calculates the points on each line where the distance between the lines
     * is minimal
     * @param otherLine        [in]  The other line.
     * @param pointOnThisLine  [out] Outputs the point on this line.
     * @param pointOnOtherLine [out] Outputs the point on the other line.
     * @return The distance between both points;
     */
    REAL NearestPoints(const Line3 &otherLine, ::Vector3 &pointOnThisLine, ::Vector3 &pointOnOtherLine);
    
    friend class Segment3;
};

#endif /* defined(__BDEMath__Line3__) */
