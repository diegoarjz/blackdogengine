//
//  Segment3.h
//  BDEMath
//
//  Created by Diego Jesus on 29/04/14.
//  Copyright (c) 2014 BlackDogEngine. All rights reserved.
//

#ifndef __BDEMath__Segment3__
#define __BDEMath__Segment3__

#include "MathLibConfigurations.h"

#include <iostream>
#include <CGAL/Cartesian.h>

#include "Line3.h"
#include "Vector3.h"
#include "Ray3.h"

typedef CGAL::Cartesian<REAL>::Segment_3 Segment_3;

class Segment3{
private:
    Segment_3 mSegment;
public:
    
    /* ****************************
     * Construction & Destruction *
     * ***************************/
    Segment3();
    Segment3(const Vector3 &source, const Vector3 &target);
    Segment3(const Segment3 &segment);
    
#if CGAL_COMPATIBLE == 1
    Segment3(const Segment_3 &segmet);
    operator Segment_3 () const;
#endif
    
    ~Segment3();

    /* *******************
     * Getters & Setters *
     * ******************/
    ::Vector3 Source() const;
    ::Vector3 Target() const;
    
    REAL Length() const;
    
    ::Vector3 Direction() const;
    
    /* ************
     * Operations *
     * ***********/
    ::Line3 SupportingLine() const;
    
    REAL SquaredDistance(const Line3 &line) const;
    REAL Distance(const Line3 &line) const;
    REAL SquaredDistance(const Ray3 &ray) const;
    REAL Distance(const Ray3 &ray) const;
    REAL SquaredDistance(const Segment3 &segment) const;
    REAL Distance(const Segment3 &segment) const;
    
    friend bool operator==(const Segment3 &segment1, const Segment3 &segment2);
};

#else
class Segment3;

#endif /* defined(__BDEMath__Segment3__) */
