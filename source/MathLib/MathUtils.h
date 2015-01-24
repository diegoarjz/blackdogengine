//
//  MathUtils.h
//  BDEMath
//
//  Created by Diego Jesus on 10/09/14.
//  Copyright (c) 2014 BlackDogEngine. All rights reserved.
//

#ifndef __BDEMath__MathUtils__
#define __BDEMath__MathUtils__

#include "MathLibConfigurations.h"

#include "MathLib.h"

#include <iostream>
#include <list>

class MathUtils{
public:
    
    static REAL LinearInterpolation(const REAL& x0, const REAL& x1, const REAL& y0, const REAL& y1, const REAL& x);
    
    /**
     * Calculates and returns the following function:
     *  f(a,b) = e^( - a^2/b^2 )
     */
    static REAL Gaussian(const REAL &a, const REAL &b);
    
    /**
     * Calculates the 2D centroid of a list of points.
     */
    static ::Vector2 Centroid(std::list<::Vector2> points);
    /**
     * Calculates the 3D centroid of a list of points.
     */
    static ::Vector3 Centroid(std::list<::Vector3> points);
};

#else
class MathUtils;
#endif /* defined(__BDEMath__MathUtils__) */
