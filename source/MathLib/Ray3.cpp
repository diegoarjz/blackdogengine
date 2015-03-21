//
//  Ray3.cpp
//  BDEMath
//
//  Created by Diego Jesus on 29/04/14.
//  Copyright (c) 2014 BlackDogEngine. All rights reserved.
//

#include "Ray3.h"

namespace bde{
    
    /* ****************************
     * Construction & Destruction *
     * ***************************/
    Ray3::Ray3():Ray3(Vector3(0,0,0), Vector3(1,0,0)){
        
    }
    
    Ray3::Ray3(const Vector3 &origin, const Vector3 direction){
        mRay = Ray_3(Point_3(origin.X(), origin.Y(), origin.Z()),
                     Direction_3(direction.X(), direction.Y(), direction.Z()));
    }
    
    Ray3::Ray3(const Ray3 &r){
        mRay = r.mRay;
    }
    
    
#if CGAL_COMPATIBLE == 1
    Ray3::Ray3(const Ray_3 &ray){
        mRay = ray;
    }
    
    Ray3::operator Ray_3() const{
        return mRay;
    }
#endif
    
    Line3 Ray3::SupportingLine() const{
        Line_3 rayLine = mRay.supporting_line();
        Point_3 point = rayLine.point();
        Direction_3 direction = rayLine.direction();
        return Line3(point, direction);
    }
    
    /* ************
     * Operations *
     * ***********/
    REAL Ray3::SquaredDistance(const Ray3 &ray){
        return CGAL::squared_distance(mRay, ray.mRay);
    }
    
    REAL Ray3::Distance(const Ray3 &ray){
        return sqrtf(SquaredDistance(ray));
    }
    
    REAL Ray3::SquaredDistance(const Vector3 &v) const{
        return CGAL::squared_distance(mRay, Point_3(v));
    }
    
    REAL Ray3::Distance(const Vector3 &v) const{
        return sqrtf(SquaredDistance(v));
    }
    
} // namespace bde