//
//  MathUtils.cpp
//  BDEMath
//
//  Created by Diego Jesus on 10/09/14.
//  Copyright (c) 2014 BlackDogEngine. All rights reserved.
//

#include "MathUtils.h"
#include <cmath>
#include <cassert>

namespace bde {
    REAL MathUtils::LinearInterpolation(const REAL &x0, const REAL &x1,
                                        const REAL &y0, const REAL &y1, const REAL &x) {
        return y0 + (y1-y0)*((x-x0)/(x1-x0));
    }

    REAL MathUtils::Gaussian(const REAL &a, const REAL &b) {
        return exp( - (a*a)/(b*b) );
    }

    Vector2 MathUtils::Centroid(std::list<Vector2> points) {
        Vector2 centroid(0,0);

        for(auto p : points) {
            centroid = centroid + p;
        }

        centroid = centroid/points.size();
        return centroid;
    }

    Vector3 MathUtils::Centroid(std::list<Vector3> points) {
        Vector3 centroid(0,0,0);

        for(auto p : points) {
            centroid = centroid + p;
        }

        centroid = centroid/points.size();
        return centroid;
    }
} // namespace bde