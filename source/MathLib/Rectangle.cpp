//
//  Rectangle.cpp
//  BDEMath
//
//  Created by Diego Jesus on 10/06/14.
//  Copyright (c) 2014 BlackDogEngine. All rights reserved.
//

#include "Rectangle.h"

namespace bde {

    /* ****************************
     * Construction & Destruction *
     * ***************************/
    Rectangle::Rectangle():mPosition(0,0), mSize(0,0) {
    }

    Rectangle::Rectangle(const Vector2<> &position, const Vector2<> &size,
                         const Positions &positionCorner) {
        SetSize(size);
        SetPosition(position, positionCorner);
    }

    Rectangle::Rectangle(const Rectangle &other) {
        mPosition = other.mPosition;
        mSize = other.mSize;
    }

    /* *******************
     * Getters & Setters *
     * ******************/
    Vector2<> Rectangle::GetPosition(const Positions &positionCorner) const {
        return mPosition + getPositionVector(positionCorner);
    }

    void Rectangle::SetPosition(const Vector2<> &position,
                                const Positions &positionCorner) {
        Vector2<> pos = getPositionVector(positionCorner);
        mPosition = position - pos;
    }

    Vector2<> Rectangle::GetSize() const {
        return mSize;
    }

    void Rectangle::SetSize(const Vector2<> &size) {
        mSize = size;
    }

    Vector2<> Rectangle::GetBottomLeft() const {
        return mPosition;
    }

    Vector2<> Rectangle::GetBottomRight() const {
        return mPosition + getPositionVector(BottomRight);
    }

    Vector2<> Rectangle::GetTopRight() const {
        return mPosition + getPositionVector(TopRight);
    }

    Vector2<> Rectangle::GetTopLeft() const {
        return mPosition + getPositionVector(TopLeft);
    }

    REAL Rectangle::GetDiagonalLength() const {
        return getPositionVector(TopRight).Length();
    }

    Vector2<> Rectangle::GetDiagonal() const {
        return getPositionVector(TopRight);
    }

    /* ************
     * Operations *
     * ***********/
    bool Rectangle::Intersects(const Rectangle &other) const {
        Vector2<> thisX(mPosition.X(),mPosition.X() + mSize.X());
        Vector2<> thisY(mPosition.Y(),mPosition.Y() + mSize.Y());
        Vector2<> otherX(other.mPosition.X(),other.mPosition.X() + other.mSize.X());
        Vector2<> otherY(other.mPosition.Y(),other.mPosition.Y() + other.mSize.Y());
        return  thisX.X() < otherX.Y() &&
                thisX.Y() > otherX.X() &&
                thisY.X() < otherY.Y() &&
                thisY.Y() > otherY.X();
    }

    void Rectangle::Grow(const Rectangle &other) {
        REAL minX = mPosition.X();
        REAL minY = mPosition.Y();
        REAL maxX = mPosition.X() + mSize.X();
        REAL maxY = mPosition.Y() + mSize.Y();
        Vector2<> otherPos[] = {
            other.GetPosition(BottomLeft),
            other.GetPosition(BottomRight),
            other.GetPosition(TopRight),
            other.GetPosition(TopLeft)
        };

        for (int i=0; i<4; ++i) {
            Vector2<> corner = otherPos[i];

            if(corner.X() < minX) {
                minX = corner.X();
            }

            if(corner.X() > maxX) {
                maxX = corner.X();
            }

            if(corner.Y() < minY) {
                minY = corner.Y();
            }

            if(corner.Y() > maxY) {
                maxY = corner.Y();
            }
        }

        mPosition = Vector2<>(minX, minY);
        mSize = Vector2<>(maxX-minX, maxY-minY);
    }

    bool Rectangle::IsInside(const Vector2<> &point) const {
        Vector2<> topLeft = getPositionVector(TopLeft);
        Vector2<> bottomRight = getPositionVector(BottomRight);
        float x = point.X();
        float y = point.Y();

        if(y < topLeft.Y() && y > bottomRight.Y() &&
                x > topLeft.X() && x < bottomRight.X()) {
            return true;
        }

        return false;
    }

    Vector2<> Rectangle::getPositionVector(const Positions &position) const {
        switch (position) {
        case BottomLeft:
            return Vector2<>(0,0);

        case BottomRight:
            return Vector2<>(mSize.X(), 0);

        case TopRight:
            return Vector2<>(mSize.X(), mSize.Y());

        case TopLeft:
            return Vector2<>(0,mSize.Y());

        case Center:
            return Vector2<>(mSize.X()*0.5, mSize.Y()*0.5);

        default:
            break;
        }
    }


    std::ostream &operator<<(std::ostream &o, const Rectangle &r) {
        o << "Position: " << r.mPosition << " Size: " << r.mSize;
        return o;
    }
}