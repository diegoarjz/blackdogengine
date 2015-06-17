//
//  Vector4.cpp
//  BDEMath
//
//  Created by Diego Jesus on 29/04/14.
//  Copyright (c) 2014 BlackDogEngine. All rights reserved.
//

#include "Vector4.h"
#include <glm/gtx/norm.hpp>

namespace bde {
    /* ****************************
     * Construction & Destruction *
     * ***************************/
    Vector4::Vector4():mVector(0,0,0,0) {
    }

    Vector4::Vector4(const REAL &x, const REAL &y, const REAL &z,
                     const REAL &w):mVector(x,y,z,w) {
    }

    Vector4::Vector4(const Vector4 &v) {
        mVector = v.mVector;
    }

    Vector4::~Vector4() {
    }

#if GLM_COMPATIBLE == 1
    Vector4::Vector4(const glm::vec4 &v) {
        mVector = v;
    }

    Vector4::operator glm::vec4() const {
        return mVector;
    }
#endif

    /* *******************
     * Getters & Setters *
     * ******************/
    REAL Vector4::X() const {
        return mVector.x;
    }

    REAL Vector4::Y() const {
        return mVector.y;
    }

    REAL Vector4::Z() const {
        return mVector.z;
    }

    REAL Vector4::W() const {
        return mVector.w;
    }

    REAL Vector4::SquaredLength() const {
        return glm::length2(mVector);
    }

    REAL Vector4::Length() const {
        return glm::length(mVector);
    }

    /* ************
     * Operations *
     * ***********/
    Vector4 Vector4::operator+(const Vector4 &v) const {
        return mVector + v.mVector;
    }

    Vector4 Vector4::operator+=(const Vector4 &v) {
        mVector += v.mVector;
        return *this;
    }

    Vector4 Vector4::operator-(const Vector4 &v) const {
        return mVector - v.mVector;
    }

    Vector4 Vector4::operator-=(const Vector4 &v) {
        mVector -= v.mVector;
        return *this;
    }

    Vector4 operator*(const REAL &s, const Vector4 &v) {
        return s*v.mVector;
    }

    Vector4 Vector4::operator*(const REAL &s) {
        return mVector*s;
    }

    Vector4 Vector4::operator*(const Matrix4 &m) {
        glm::mat4 mat = m;
        return mVector * mat;
    }

    REAL Vector4::Normalize() {
        REAL length = Length();
        mVector = glm::normalize(mVector);
        return length;
    }

    std::ostream &operator<< (std::ostream &o, const Vector4 &v) {
        o << "[" << v.X() << ", " << v.Y() << ", " << v.Z() << ", " << v.W() << "]";
        return o;
    }

} // namespace bde