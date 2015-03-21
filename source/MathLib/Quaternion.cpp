//
//  Quaternion.cpp
//  BDEMath
//
//  Created by Diego Jesus on 29/04/14.
//  Copyright (c) 2014 BlackDogEngine. All rights reserved.
//

#include "Quaternion.h"
#include <glm/gtx/norm.hpp>

namespace bde{
    /* ****************************
     * Construction & Destruction *
     * ***************************/
    Quaternion::Quaternion():mQuaternion(){
        
    }
    
    Quaternion::Quaternion(const REAL &x, const REAL &y, const REAL &z, const REAL &w){
        mQuaternion = glm::quat(w,x,y,z);
    }
    
    Quaternion::Quaternion(const Quaternion &q){
        mQuaternion = q.mQuaternion;
    }
    
    Quaternion::~Quaternion(){
        
    }
    
#if GLM_COMPATIBLE == 1
    Quaternion::Quaternion(const glm::quat &q){
        mQuaternion = q;
    }
    
    Quaternion::operator glm::quat() const{
        return mQuaternion;
    }
#endif
    
    /* *******************
     * Getters & Setters *
     * ******************/
    REAL Quaternion::X() const{
        return mQuaternion.x;
    }
    
    REAL Quaternion::Y() const{
        return mQuaternion.y;
    }
    
    REAL Quaternion::Z() const{
        return mQuaternion.z;
    }
    
    REAL Quaternion::W() const{
        return mQuaternion.w;
    }
    
    /* ****************
     * Static Methods *
     * ***************/
    Quaternion Quaternion::RotationBetweenVectors(const Vector3 &v1, const Vector3 &v2){
        glm::vec3 start = glm::normalize(glm::vec3(v1.X(), v1.Y(), v1.Z()));
        glm::vec3 dest = glm::normalize(glm::vec3(v2.X(), v2.Y(), v2.Z()));
        
        REAL cosTheta = glm::dot(start, dest);
        glm::vec3 rotationAxis;
        
        if (cosTheta < -1 + 0.001f){
            // special case when vectors in opposite directions :
            // there is no "ideal" rotation axis
            // So guess one; any will do as long as it's perpendicular to start
            // This implementation favors a rotation around the Up axis,
            // since it's often what you want to do.
            rotationAxis = glm::cross(glm::vec3(0.0f, 0.0f, 1.0f), start);
            if (glm::length2(rotationAxis) < 0.01 ) // bad luck, they were parallel, try again!
                rotationAxis = glm::cross(glm::vec3(1.0f, 0.0f, 0.0f), start);
            
            rotationAxis = glm::normalize(rotationAxis);
            glm::quat ret = (glm::angleAxis(180.0f, rotationAxis));
            return Quaternion(ret.x, ret.y, ret.z, ret.w);
        }
        
        // Implementation from Stan Melax's Game Programming Gems 1 article
        rotationAxis = glm::cross(start, dest);
        
        REAL s = sqrt( (1+cosTheta)*2 );
        REAL invs = 1 / s;
        
        return Quaternion(rotationAxis.x * invs,
                          rotationAxis.y * invs,
                          rotationAxis.z * invs,
                          s * 0.5f
                          );
    }
} // namespace bde