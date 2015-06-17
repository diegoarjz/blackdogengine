//
//  Vector2.cpp
//  BDEMath
//
//  Created by Diego Jesus on 29/04/14.
//  Copyright (c) 2014 BlackDogEngine. All rights reserved.
//

#include "Vector2.h"
#include <glm/gtx/norm.hpp>

namespace bde {
    /* ****************************
     * Construction & Destruction *
     * ***************************/
    Vector2::Vector2() {
        mVector = glm::vec2(0,0);
    }

    Vector2::Vector2(const REAL &x, const REAL &y) {
        mVector = glm::vec2(x,y);
    }

    Vector2::Vector2(const Vector2 &v) {
        mVector = v.mVector;
    }

    Vector2::~Vector2() {
    }

#if GLM_COMPATIBLE == 1
    Vector2::Vector2(const glm::vec2 &v) {
        mVector = v;
    }

    Vector2::operator glm::vec2() const {
        return mVector;
    }
#endif

#if CGAL_COMPATIBLE == 1
    Vector2::Vector2(const Vector_2 &v) {
        mVector = glm::vec2(v.x(), v.y());
    }

    Vector2::Vector2(const Point_2 &v) {
        mVector = glm::vec2(v.x(), v.y());
    }

    Vector2::Vector2(const Direction_2 &v) {
        mVector = glm::vec2(v.dx(), v.dy());
    }

    Vector2::operator Vector_2() const {
        return Vector_2(mVector.x, mVector.y);
    }

    Vector2::operator Point_2() const {
        return Point_2(mVector.x, mVector.y);
    }

    Vector2::operator Direction_2() const {
        return Direction_2(mVector.x, mVector.y);
    }
#endif

    /* *******************
     * Getters & Setters *
     * ******************/
    const REAL &Vector2::X() const {
        return mVector.x;
    }

    REAL &Vector2::X() {
        return mVector.x;
    }

    const REAL &Vector2::Y() const {
        return mVector.y;
    }

    REAL &Vector2::Y() {
        return mVector.y;
    }

    REAL Vector2::SquaredLength() {
        return glm::length2(mVector);
    }

    REAL Vector2::Length() {
        return glm::length(mVector);
    }

    /* ************
     * Operations *
     * ***********/
    Vector2 Vector2::operator+(const Vector2 &v) const {
        return Vector2(mVector + v.mVector);
    }

    Vector2 Vector2::operator-(const Vector2 &v) const {
        return Vector2(mVector - v.mVector);
    }

    Vector2 Vector2::operator*(const REAL &f) const {
        return Vector2(mVector*f);
    }

    Vector2 operator*(const REAL &f, const Vector2 &v) {
        return Vector2(f*v.mVector);
    }

    Vector2 Vector2::operator/(const REAL &f) const {
        return Vector2(mVector/f);
    }

    Vector2 operator/(const REAL &f, const Vector2 &v) {
        return Vector2(f/v.mVector);
    }

    REAL Vector2::Dot(const Vector2 &v) const {
        return glm::dot(mVector, v.mVector);
    }

    /* *************
     * Comparisons *
     * ************/
    bool Vector2::operator==(const Vector2 &v) const {
        return mVector == v.mVector;
    }

    bool Vector2::operator!=(const Vector2 &v) const {
        return !(*this == v);
    }

    std::ostream &operator<<(std::ostream &o, const Vector2 &v) {
        o << "[ " << v.X() << ", " << v.Y() << " ]";
        return o;
    }
} // namespace bde