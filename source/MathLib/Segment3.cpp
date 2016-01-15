//
//  Segment3.cpp
//  BDEMath
//
//  Created by Diego Jesus on 29/04/14.
//  Copyright (c) 2014 BlackDogEngine. All rights reserved.
//

#include "Segment3.h"

namespace bde {
    /* ****************************
     * Construction & Destruction *
     * ***************************/
    Segment3::Segment3():Segment3(Vector3<>(0,0,0), Vector3<>(1,0,0)) {
    }

    Segment3::Segment3(const Vector3<> &source, const Vector3<> &target) {
        mSegment = Segment_3(Point_3(source.X(), source.Y(), source.Z()),
                             Point_3(target.X(), target.Y(), target.Z()));
    }

    Segment3::Segment3(const Segment3 &segment) {
        mSegment = segment.mSegment;
    }

    Segment3::~Segment3() {
    }

#if CGAL_COMPATIBLE == 1
    Segment3::Segment3(const Segment_3 &segment) {
        mSegment = segment;
    }

    Segment3::operator Segment_3() const {
        return mSegment;
    }
#endif

    /* *******************
     * Getters & Setters *
     * ******************/
    Vector3<> Segment3::Source() const {
        return Vector3<>(mSegment.source().x(),
                       mSegment.source().y(),
                       mSegment.source().z());
    }

    Vector3<> Segment3::Target() const {
        return Vector3<>(mSegment.target().x(),
                       mSegment.target().y(),
                       mSegment.target().z());
    }

    REAL Segment3::Length() const {
        return (Target()-Source()).Length();
    }

    Vector3<> Segment3::Direction() const {
        return Vector3<>(mSegment.direction());
    }

    /* ************
     * Operations *
     * ***********/
    Line3 Segment3::SupportingLine() const {
        return Line3(mSegment.source(), mSegment.target()-mSegment.source());
    }

    REAL Segment3::SquaredDistance(const Line3 &line) const {
        return CGAL::squared_distance(mSegment, line.mLine);
    }

    REAL Segment3::Distance(const Line3 &line) const {
        return sqrt(SquaredDistance(line));
    }

    REAL Segment3::SquaredDistance(const Ray3 &ray) const {
        return CGAL::squared_distance(mSegment, ray.mRay);
    }

    REAL Segment3::Distance(const Ray3 &ray) const {
        return sqrt(SquaredDistance(ray));
    }

    REAL Segment3::SquaredDistance(const Segment3 &segment) const {
        return CGAL::squared_distance(mSegment, segment.mSegment);
    }

    REAL Segment3::Distance(const Segment3 &segment) const {
        return sqrt(SquaredDistance(segment));
    }

    bool operator==(const Segment3 &segment1, const Segment3 &segment2) {
        return segment1.mSegment == segment2.mSegment;
    }
} // namespace bde