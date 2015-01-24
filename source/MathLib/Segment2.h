//
//  Segment2.h
//  BDEMath
//
//  Created by Diego Jesus on 29/04/14.
//  Copyright (c) 2014 BlackDogEngine. All rights reserved.
//

#ifndef __BDEMath__Segment2__
#define __BDEMath__Segment2__

#include "MathLibConfigurations.h"

#include <iostream>
#include <CGAL/Cartesian.h>

#include "Vector2.h"

typedef CGAL::Cartesian<REAL>::Segment_2 Segment_2;

class Segment2{
private:
    Segment_2 mSegment;
public:
    
    /* ****************************
     * Construction & Destruction *
     * ***************************/
    Segment2();
    Segment2(const Vector2& source, const Vector2 &target);
    Segment2(const Segment2& segment);
    ~Segment2();
    
#if CGAL_COMPATIBLE == 1
    Segment2(const Segment_2 &s);
    operator Segment_2() const;
#endif
    
    /* *******************
     * Getters & Setters *
     * ******************/
    Vector2 Source() const;
    Vector2 Target() const;
    
    /* ************
     * Operations *
     * ***********/
    REAL SquaredDistance(const ::Vector2 &point) const;
    REAL Distance(const ::Vector2 &point) const;
    
    bool Intersects(const ::Segment2 &segment) const;
};
#endif /* defined(__BDEMath__Segment2__) */
