//
//  AABoundingBox.h
//  BDEMath
//
//  Created by Diego Jesus on 13/01/15.
//  Copyright (c) 2015 BlackDogEngine. All rights reserved.
//

#ifndef __BDEMath__AABoundingBox__
#define __BDEMath__AABoundingBox__

#include <iostream>

#include "MathLib.h"

namespace bde {
    
    /**
     * Axis Aligned Bounding Box.
     *
     * @author  Diego Jesus <diego.a.r.jz@gmail.com>
     * @date    13 Jan. 2015
     */
    class AABoundingBox{
    public:
        /**
         * Names of the points in the AABoundingBox.
         */
        enum class PointName{
                                     // Binary Representation
                                     // zyx
            LowerBottomLeft     = 0, // 000
            LowerBottomRight    = 1, // 001
            LowerTopLeft        = 2, // 010
            LowerTopRight       = 3, // 011
            
            HigherBottomLeft    = 4, // 100
            HigherBottomRight   = 5, // 101
            HigherTopLeft       = 6, // 110
            HigherTopRight      = 7, // 111
        };
    private:
        /// The minimum coordinates for all 3 axis.
        Vector3 mBounds[2];
        /// Indicates that this bounding volume is null
        bool mIsNull;
    public:
        /* ****************************
         * Construction & Destruction *
         * ***************************/
        AABoundingBox();
        AABoundingBox(const Vector3 &min, const Vector3 &max);
        ~AABoundingBox();
        
        /* *******************
         * Getters & Setters *
         * ******************/
        Vector3 GetPoint(const PointName &pointName) const;
        /**
         * Calculates and returns all 8 points defined in the AABB.
         * The output will be ordered by PointName enum.
         * @param points [out] An array of 8 Vector3.
         */
        void    GetPoints(Vector3 *points);
        REAL    SizeX() const;
        REAL    SizeY() const;
        REAL    SizeZ() const;
        bool    IsNull() const;
        void    SetNull(const bool &null);
        
        /**
         * Grows the AABB if the point is outside the box,
         * so that it contains the point.
         */
        void GrowToContain(const Vector3 &point);
        
    }; // class AABoundingBox
}

#else
namespace bde{
    class AABoundingBox;
}
#endif /* defined(__BDEMath__AABoundingBox__) */
