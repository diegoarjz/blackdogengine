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

    Vector2<> MathUtils::Centroid(std::list<Vector2<>> points) {
        Vector2<> centroid(0,0);

        /*
        for(auto p : points) {
            centroid = centroid + p;
        }

        centroid = centroid/points.size();
         */
        return centroid;
    }

    Vector3<> MathUtils::Centroid(std::list<Vector3<>> points) {
        Vector3<> centroid(0,0,0);

        /*
        for(auto p : points) {
            centroid = centroid + p;
        }

        centroid = centroid/points.size();
         */
        return centroid;
    }
    
    REAL MathUtils::ToRadians(const REAL &degree){
#warning TODO: create a constant for Pi somewhere
        return degree * 3.14159265358979323846 / 180;
    }
} // namespace bde