//
//  Line2.cpp
//  BDEMath
//
//  Created by Diego Jesus on 29/04/14.
//  Copyright (c) 2014 BlackDogEngine. All rights reserved.
//

#include "Line2.h"

namespace bde {
    /* ****************************
     * Construction & Destruction *
     * ***************************/
    Line2::Line2():Line2(Vector2(0,0), Vector2(1,0)) {
    }

    Line2::Line2(const Vector2 &origin, const Vector2 &direction) {
        Direction_2 dir = direction ;
        mLine = Line_2(Point_2(origin),
                       dir);
    }

    Line2::Line2(const Line2 &line) {
        mLine = line.mLine;
    }

    Line2::~Line2() {
    }

#if CGAL_COMPATIBLE == 1
    Line2::Line2(const Line_2 &line) {
        mLine = line;
    }

    Line2::operator Line_2() const {
        return mLine;
    }
#endif

    /* *******************
     * Getters & Setters *
     * ******************/
    Vector2 Line2::Point() const {
        return Vector2(mLine.point());
    }

    Vector2 Line2::Vector() const {
        return Vector2(mLine.to_vector());
    }

    /* ************
     * Operations *
     * ***********/
    REAL Line2::SquaredDistance(const Line2 &line) const {
        return CGAL::squared_distance(mLine, line.mLine);
    }

    REAL Line2::Distance(const Line2 &line) const {
        return sqrtf( SquaredDistance(line) );
    }

    REAL Line2::SquaredDistance(const Vector2 &p) const {
        return CGAL::squared_distance(mLine, Point_2(p));
    }

    REAL Line2::Distance(const Vector2 &p) const {
        return sqrtf( SquaredDistance(p) );
    }

    Vector2 Line2::Projection(const Vector2 &point) const {
        return Vector2( mLine.projection(Point_2(point)));
    }
} // namespace bde