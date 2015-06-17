//
//  Quaternion.h
//  BDEMath
//
//  Created by Diego Jesus on 29/04/14.
//  Copyright (c) 2014 BlackDogEngine. All rights reserved.
//

#ifndef __BDEMath__Quaternion__
#define __BDEMath__Quaternion__

#include "MathLibConfigurations.h"

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include "Vector3.h"

namespace bde {
    class Quaternion {
      private:
        glm::quat mQuaternion;

      public:
        /* ****************************
         * Construction & Destruction *
         * ***************************/
        Quaternion();
        Quaternion(const REAL &x, const REAL &y, const REAL &z, const REAL &w);
        Quaternion(const Quaternion &q);
        ~Quaternion();

#if GLM_COMPATIBLE == 1
        Quaternion(const glm::quat &q);
        operator glm::quat() const;
#endif

        /* *******************
         * Getters & Setters *
         * ******************/
        REAL X() const;
        REAL Y() const;
        REAL Z() const;
        REAL W() const;

        /* ****************
         * Static Methods *
         * ***************/
        static Quaternion RotationBetweenVectors(const Vector3 &v1, const Vector3 &v2);
    };
} // namespace bde

#else
namespace bde {
    class Quaternion;
} // namespace bde
#endif /* defined(__BDEMath__Quaternion__) */
