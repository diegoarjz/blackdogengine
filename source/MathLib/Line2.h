//
//  Line2.h
//  BDEMath
//
//  Created by Diego Jesus on 29/04/14.
//  Copyright (c) 2014 BlackDogEngine. All rights reserved.
//

#ifndef __BDEMath__Line2__
#define __BDEMath__Line2__

#include "MathLibConfigurations.h"

#include <iostream>
#include <CGAL/Cartesian.h>
#include "Vector2.h"

namespace bde{
    typedef CGAL::Cartesian<REAL>::Line_2 Line_2;
    
    class Line2{
    private:
        Line_2 mLine;
    public:
        /* ****************************
         * Construction & Destruction *
         * ***************************/
        Line2();
        Line2(const Vector2 &origin, const Vector2 &direction);
        Line2(const Line2 &line);
        ~Line2();
        
#if CGAL_COMPATIBLE == 1
        Line2(const Line_2 &line);
        operator Line_2() const;
#endif
        
        /* *******************
         * Getters & Setters *
         * ******************/
        Vector2 Point() const;
        Vector2 Vector() const;
        
        /* ************
         * Operations *
         * ***********/
        REAL SquaredDistance(const Line2 &line) const;
        REAL Distance(const Line2 &line) const;
        REAL SquaredDistance(const Vector2 &p) const;
        REAL Distance(const Vector2 &p) const;
        Vector2 Projection(const Vector2 &point) const;
    };
} // namespace bde

#else

namespace bde{
    class Line2;
} // namespace bde

#endif /* defined(__BDEMath__Line2__) */
