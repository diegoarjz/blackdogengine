//
//  Rectangle.h
//  BDEMath
//
//  Created by Diego Jesus on 10/06/14.
//  Copyright (c) 2014 BlackDogEngine. All rights reserved.
//

#ifndef __BDEMath__Rectangle__
#define __BDEMath__Rectangle__

#include "MathLibConfigurations.h"

#include <iostream>
#include "Vector2.h"

namespace bde{
    
    /**
     * Defines a rectangle in the XY Plane. The rectangle's position is considered to be
     * the bottom left corner. However, it is possible to get and set its positions relative
     * to the other corners and the center.
     */
    class Rectangle{
    public:
        /// Enum defining the positions.
        enum Positions{
            /// Bottom left corner.
            BottomLeft,
            /// Bottom right corner.
            BottomRight,
            /// Top right corner.
            TopRight,
            /// Top left corner.
            TopLeft,
            /// Center
            Center
        };
    private:
        /// The rectangle's position, always stored relative to the bottom Left corner.
        ::Vector2 mPosition;
        ///  The rectangle's size
        ::Vector2 mSize;
        
    public:
        
        /* ****************************
         * Construction & Destruction *
         * ***************************/
        Rectangle();
        Rectangle(const ::Vector2 &position, const ::Vector2 &size, const Positions &positionCorner = BottomLeft);
        Rectangle(const Rectangle &other);
        
        /* *******************
         * Getters & Setters *
         * ******************/
        ::Vector2 GetPosition(const Positions &positionCorner = BottomLeft) const;
        void SetPosition(const ::Vector2 &position, const Positions &positionCorner = BottomLeft);
        ::Vector2 GetSize() const;
        void SetSize(const ::Vector2 &size);
        
        ::Vector2 GetBottomLeft() const;
        ::Vector2 GetBottomRight() const;
        ::Vector2 GetTopRight() const;
        ::Vector2 GetTopLeft() const;
        
        REAL GetDiagonalLength() const;
        ::Vector2 GetDiagonal() const;
        
        /* ************
         * Operations *
         * ***********/
        bool Intersects(const Rectangle &other) const;
        void Grow(const Rectangle &other);
        bool IsInside(const ::Vector2 &point) const;
        
        friend std::ostream& operator<<(std::ostream &o, const Rectangle &r);
    private:
        ::Vector2 getPositionVector(const Positions &position) const;
    };
}

#else
namespace bde{
    class Rectangle;
}
#endif /* defined(__BDEMath__Rectangle__) */
