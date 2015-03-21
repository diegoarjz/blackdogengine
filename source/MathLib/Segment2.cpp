//
//  Segment2.cpp
//  BDEMath
//
//  Created by Diego Jesus on 29/04/14.
//  Copyright (c) 2014 BlackDogEngine. All rights reserved.
//

#include "Segment2.h"

namespace bde{
    /* ****************************
     * Construction & Destruction *
     * ***************************/
    
    Segment2::Segment2():Segment2(Vector2(0,0), Vector2(1,0)){
        
    }
    
    Segment2::Segment2(const Vector2& source, const Vector2 &target){
        mSegment = Segment_2(Point_2(source.X(), source.Y()),
                             Point_2(target.X(), target.Y()));
    }
    
    Segment2::Segment2(const Segment2& segment){
        mSegment = segment.mSegment;
    }
    
    Segment2::~Segment2(){
        
    }
    
#if CGAL_COMPATIBLE == 1
    Segment2::Segment2(const Segment_2 &s){
        mSegment = s;
    }
    
    Segment2::operator Segment_2() const{
        return mSegment;
    }
#endif
    
    /* *******************
     * Getters & Setters *
     * ******************/
    Vector2 Segment2::Source() const{
        return Vector2(mSegment.source().x(), mSegment.source().y());
    }
    
    Vector2 Segment2::Target()const {
        return Vector2(mSegment.target().x(), mSegment.target().y());
    }
    
    /* ************
     * Operations *
     * ***********/
    REAL Segment2::SquaredDistance(const Vector2 &point) const{
        Point_2 p(point.X(), point.Y());
        return CGAL::squared_distance(mSegment, p);
    }
    
    REAL Segment2::Distance(const Vector2 &point) const{
        return sqrtf(SquaredDistance(point));
    }
    
    bool Segment2::Intersects(const Segment2 &segment) const{
        return CGAL::do_intersect(mSegment, segment.mSegment);
    }
    
} // namespace bde