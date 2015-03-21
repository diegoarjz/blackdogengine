//
//  Vector3.cpp
//  BDEMath
//
//  Created by Diego Jesus on 29/04/14.
//  Copyright (c) 2014 BlackDogEngine. All rights reserved.
//

#include "Vector3.h"
#include <glm/gtx/norm.hpp>

namespace bde{
    /* ****************************
     * Construction & Destruction *
     * ***************************/
    Vector3::Vector3():mVector(0,0,0){
        
    }
    
    Vector3::Vector3(const REAL &x, const REAL &y, const REAL &z):mVector(x,y,z){
        
    }
    
    Vector3::Vector3(const Vector3& v){
        mVector = v.mVector;
    }
    
#if GLM_COMPATIBLE == 1
    Vector3::Vector3(const glm::vec3 &v){
        mVector = v;
    }
    
    Vector3::operator glm::vec3() const{
        return mVector;
    }
#endif
    
#if CGAL_COMPATIBLE == 1
    Vector3::Vector3(const Point_3 &p){
        mVector = glm::vec3(p.x(), p.y(), p.z());
    }
    
    Vector3::Vector3(const Vector_3 &p){
        mVector = glm::vec3(p.x(), p.y(), p.z());
    }
    
    Vector3::Vector3(const Direction_3 &p){
        mVector = glm::vec3(p.dx(), p.dy(), p.dz());
    }
    
    Vector3::operator Vector_3() const{
        return Vector_3(mVector.x, mVector.y, mVector.z);
    }
    
    Vector3::operator Point_3() const{
        return Point_3(mVector.x, mVector.y, mVector.z);
    }
    
    Vector3::operator Direction_3() const{
        return Direction_3(mVector.x, mVector.y, mVector.z);
    }
#endif
    
    Vector3::~Vector3(){
        
    }
    
    /* *******************
     * Getters & Setters *
     * ******************/
    REAL Vector3::X() const{
        return mVector.x;
    }
    
    REAL Vector3::Y() const{
        return mVector.y;
    }
    
    REAL Vector3::Z() const{
        return mVector.z;
    }
    
    REAL Vector3::SquaredLength() const{
        return glm::length2(mVector);
    }
    
    REAL Vector3::Length() const{
        return glm::length(mVector);
    }
    
    REAL& Vector3::X(){
        return mVector.x;
    }
    
    REAL& Vector3::Y(){
        return mVector.y;
    }
    
    REAL& Vector3::Z(){
        return mVector.z;
    }
    
    /* ************
     * Operations *
     * ***********/
    Vector3 Vector3::operator+(const Vector3 &v) const{
        return Vector3(mVector + v.mVector);
    }
    
    Vector3 Vector3::operator+=(const Vector3 &v){
        mVector += v.mVector;
        return *this;
    }
    
    Vector3 Vector3::operator-(const Vector3 &v) const{
        return Vector3(mVector - v.mVector);
    }
    
    Vector3 Vector3::operator-=(const Vector3 &v){
        mVector -= v.mVector;
        return *this;
    }
    
    Vector3 Vector3::operator*(const REAL &f) const{
        return Vector3(f*mVector);
    }
    
    Vector3 operator*(const REAL &f, const Vector3 &v){
        return Vector3(f*v.mVector);
    }
    
    Vector3 Vector3::operator/(const REAL &f){
        return Vector3(mVector/f);
    }
    
    Vector3 operator/(const REAL &f, const Vector3 &v){
        return Vector3(f/v.mVector);
    }
    
    Vector3 Vector3::Cross(const Vector3 &v) const{
        return Vector3( glm::cross(mVector, v.mVector) );
    }
    
    REAL Vector3::Dot(const Vector3 &v) const{
        return glm::dot(mVector, v.mVector);
    }
    
    REAL Vector3::Normalize(){
        REAL length = glm::length(mVector);
        mVector = glm::normalize(mVector);
        return length;
    }
    
    bool Vector3::IsColinear(const Vector3 &v) const{
        Vector3 thisCopy = *this;
        Vector3 vCopy = v;
        thisCopy.Normalize();
        vCopy.Normalize();
        
        float dot = thisCopy.Dot(vCopy);
        
        return (dot >= (1-FLT_EPSILON));
    }
    
    /* *************
     * Comparators *
     * ************/
    bool Vector3::operator==(const Vector3 &v) const{
        return mVector == v.mVector;
    }
    
    bool Vector3::operator!=(const Vector3 &v) const{
        return mVector != v.mVector;
    }
    
    std::ostream& operator<< (std::ostream &o, const Vector3 &v){
        o << "[" << v.X() << ", " << v.Y() << ", " << v.Z() << "]";
        
        return o;
    }
} // namespace bde