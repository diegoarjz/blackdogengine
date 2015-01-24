//
//  Plane.cpp
//  BDEMath
//
//  Created by Diego Jesus on 29/04/14.
//  Copyright (c) 2014 BlackDogEngine. All rights reserved.
//

#include "Plane.h"

/* ****************************
 * Construction & Destruction *
 * ***************************/
Plane::Plane():Plane(::Vector3(0,0,0), ::Vector3(0,1,0)){
    
}

Plane::Plane(const ::Vector3 &point, const ::Vector3 &normal){
    mPlane = Plane_3(Point_3(point.X(), point.Y(), point.Z()),
                     Vector_3(normal.X(), normal.Y(), normal.Z()));
}

Plane::Plane(const ::Vector3 &p1, const ::Vector3 &p2, const ::Vector3 &p3){
    mPlane = Plane_3(Point_3(p1.X(), p1.Y(), p1.Z()),
                     Point_3(p2.X(), p2.Y(), p2.Z()),
                     Point_3(p3.X(), p3.Y(), p3.Z()));
}

Plane::Plane(const ::Line3 &line, const ::Vector3 point){
    mPlane = Plane_3(line, Point_3(point.X(), point.Y(), point.Z()));
}

Plane::~Plane(){
    
}

/* *******************
 * Getters & Setters *
 * ******************/
::Vector3 Plane::Normal() const{
    return ::Vector3(mPlane.orthogonal_vector());
}

::Vector3 Plane::Base() const{
    return ::Vector3(mPlane.base1());
}

::Vector3 Plane::Base2() const{
    return ::Vector3(mPlane.base2());
}

/* ************
 * Operations *
 * ***********/
PlaneIntersection Plane::Intersection(const Plane &other){
    PlaneIntersection intersection;
    
    if( mPlane == other.mPlane ){
        intersection.intersectionType = PlaneIntersection::Coplanar;
        return intersection;
    }
    
    Point_3 i1;
    CGAL::Object result = CGAL::intersection(mPlane, other.mPlane);
    if(!CGAL::assign(i1, result)){
        Line_3 il;
        if(CGAL::assign(il, result)){
            intersection.intersectionLine = Line3(il);
            intersection.intersectionType = PlaneIntersection::LineIntersection;
            return intersection;
        }
        
        intersection.intersectionType = PlaneIntersection::NoIntersection;
        return intersection;
    }
    
    intersection.intersectionPoint = i1;
    intersection.intersectionType = PlaneIntersection::PointIntersection;
    return intersection;
}

PlaneIntersection Plane::Intersection(const Line3 &line){
    PlaneIntersection intersection;
    
    Point_3 i1;
    CGAL::Object result = CGAL::intersection(mPlane, Line_3(line));
    if(!CGAL::assign(i1, result)){
        Line_3 il;
        if(CGAL::assign(il, result)){
            intersection.intersectionLine = Line3(il);
            intersection.intersectionType = PlaneIntersection::LineIntersection;
            return intersection;
        }
        
        intersection.intersectionType = PlaneIntersection::NoIntersection;
        return intersection;
    }
    
    intersection.intersectionPoint = i1;
    intersection.intersectionType = PlaneIntersection::PointIntersection;
    return intersection;
}

PlaneIntersection Plane::Intersection(const Ray3 &ray){
    PlaneIntersection intersection;
    
    Point_3 i1;
    CGAL::Object result = CGAL::intersection(mPlane, Ray_3(ray));
    if(!CGAL::assign(i1, result)){
        Line_3 il;
        if(CGAL::assign(il, result)){
            intersection.intersectionLine = Line3(il);
            intersection.intersectionType = PlaneIntersection::LineIntersection;
            return intersection;
        }
        
        intersection.intersectionType = PlaneIntersection::NoIntersection;
        return intersection;
    }
    
    intersection.intersectionPoint = i1;
    intersection.intersectionType = PlaneIntersection::PointIntersection;
    return intersection;
}


Vector3 Plane::Project(const Vector3 &v){
    return Vector3(mPlane.projection(v));
}

REAL Plane::DistanceToPoint(const Vector3 &v){
    return (v-Project(v)).Length();
}

bool Plane::Contained(const ::Vector3 &v){
    return mPlane.has_on(v);
}

bool Plane::Contained(const ::Segment3 &s){
    return mPlane.has_on(s.Source()) && mPlane.has_on(s.Target());
}
