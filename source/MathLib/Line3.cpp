//
//  Line3.cpp
//  BDEMath
//
//  Created by Diego Jesus on 29/04/14.
//  Copyright (c) 2014 BlackDogEngine. All rights reserved.
//

#include "Line3.h"
#include "Plane.h"

namespace bde{
    /* ****************************
     * Construction & Destruction *
     * ***************************/
    Line3::Line3():Line3(Vector3(0,0,0), Vector3(1,0,0)){
        
    }
    
    Line3::Line3(const Vector3 &origin, const Vector3 &direction){
        mLine = Line_3(Point_3(origin.X(), origin.Y(), origin.Z()),
                       Direction_3(direction.X(), direction.Y(), direction.Z()));
    }
    
    Line3::Line3(const Line3 &line){
        mLine = line.mLine;
    }
    
    Line3::~Line3(){
        
    }
    
#if CGAL_COMPATIBLE == 1
    Line3::Line3(const Line_3 &line){
        mLine = line;
    }
    
    Line3::operator Line_3() const{
        return mLine;
    }
#endif
    
    /* *******************
     * Getters & Setters *
     * ******************/
    Vector3 Line3::Point() const{
        return mLine.point();
    }
    
    Vector3 Line3::Vector() const{
        return mLine.to_vector();
    }
    
    /* ************
     * Operations *
     * ***********/
    REAL Line3::SquaredDistance(const Line3 &line) const{
        return CGAL::squared_distance(mLine, line.mLine);
    }
    
    REAL Line3::Distance(const Line3 &line) const{
        return sqrtf(SquaredDistance(line));
    }
    
    REAL Line3::SquaredDistance(const Vector3 &point) const{
        return CGAL::squared_distance(mLine, Point_3(point) );
    }
    
    REAL Line3::Distance(const Vector3 &point) const{
        return sqrtf(SquaredDistance(point));
    }
    
    Vector3 Line3::Projection(const Vector3 &point) const{
        return Vector3(mLine.projection(Point_3(point)));
    }
    
    REAL Line3::NearestPoints(const Line3 &otherLine, Vector3 &pointOnThisLine, Vector3 &pointOnOtherLine){
        Plane p1(*this, Point() + otherLine.Vector());
        Plane p2(*this, Point() + p1.Normal());
        
        PlaneIntersection intersection = p2.Intersection(otherLine);
        
        if(intersection.intersectionType == PlaneIntersection::PointIntersection){
            Vector3 i2 = Projection(intersection.intersectionPoint);
            
            pointOnOtherLine = intersection.intersectionPoint;
            pointOnThisLine = i2;
            
            return (pointOnOtherLine-pointOnThisLine).Length();
        }
        
        return -1;
    }
    
} // namespace bde