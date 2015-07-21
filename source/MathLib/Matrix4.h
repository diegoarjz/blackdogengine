//
//  Matrix4.h
//  BDEMath
//
//  Created by Diego Jesus on 29/04/14.
//  Copyright (c) 2014 BlackDogEngine. All rights reserved.
//

#ifndef __BDEMath__Matrix4__
#define __BDEMath__Matrix4__

#include <iostream>

#include <glm/glm.hpp>
#include "MathLibConfigurations.h"
#include "Matrix3.h"
#include "Vector4.h"
#include "Vector3.h"
#include "Quaternion.h"

namespace bde {
    class Matrix4 {
      private:
        glm::mat4 mMatrix;

      public:

        /* ****************************
         * Construction & Destruction *
         * ***************************/
        Matrix4();
        Matrix4(const Matrix4 &m);
        /**
         * Construct a matrix in the following format
         * | m00 m10 m20 m30 |
         * | m01 m11 m21 m31 |
         * | m02 m12 m22 m32 |
         * | m03 m13 m23 m33 |
         */
        Matrix4(const REAL &m00,const REAL &m10,const REAL &m20, const REAL &m30,
                const REAL &m01,const REAL &m11,const REAL &m21, const REAL &m31,
                const REAL &m02,const REAL &m12,const REAL &m22, const REAL &m32,
                const REAL &m03,const REAL &m13,const REAL &m23, const REAL &m33);
        /**
         * Constructs a matrix expanding the given Matrix3 in the following way
         * | m3 0 |
         * | 0  1 |
         */
        Matrix4(const Matrix3 &m3);
        /**
         * Constructs a rotation matrix equivalent to the 
         * quaternion.
         */
        Matrix4(const Quaternion &q);
        ~Matrix4();

#if GLM_COMPATIBLE == 1
        Matrix4(const glm::mat4 &m);
        operator glm::mat4() const;
#endif

        /* *******************
         * Getters & Setters *
         * ******************/
        Vector4 GetColumn(const int &c);
        void SetColumn(const int &index, const Vector4 &c);

        Vector4 GetRow(const int &r);
        void SetRow(const int &index, const Vector4 &r);

        REAL Get(const int &column, const int &row) const;
        void Set(const int &column, const int &row, const REAL &value);

        /* ************
         * Operations *
         * ***********/
        Vector4 operator*(const Vector4 &v)const;
        Matrix4 operator*(const Matrix4 &m)const;

        /**
         * Calculates and returns the matrix inverse
         * @return The Matrix inverse
         */
        Matrix4 Inverse() const;
        /**
         * Calculates and returns the transpose matrix.
         * @return The Transpose Matrix.
         */
        Matrix4 Transpose() const;

        friend std::ostream &operator<< (std::ostream &o, const Matrix4 &m);

      public: // static methods

        /**
         * Creates a scale matrix.
         */
        static Matrix4 ScaleMatrix(const Vector3 &scaleVector);
        /**
         * Creates a Scale Matrix.
         * @param x The amount to scale along x.
         * @param y The amount to scale along y.
         * @param z The amount to scale along z.
         * @returns A Scale Matrix
         */
        static Matrix4 ScaleMatrix(const float &x, const float &y, const float &z);
        /**
         * Creates a Rotation Matrix from Euler Angles.
         * First applies the yaw (rotation along Y), then
         * pitch (along X) and finally roll (along Z).
         * @param yaw   The amount to rotate along Y.
         * @param pitch The amount to rotate along X.
         * @param roll  The amount to rotate along Z.
         * @returns A Rotation Matrix
         */
        static Matrix4 FromEulerAnglesYXZ(const float &yaw, const float &pitch,
                                          const float &roll);
        /**
         * Creates a Translation Matrix.
         * @param x The amount to translate along x.
         * @param y The amount to translate along y.
         * @param z The amount to translate along z.
         * @returns A Translation Matrix
         */
        static Matrix4 TranslationMatrix(const float &x, const float &y,const float &z);
        /**
         * Creates a Translation Matrix.
         * @param translation The translation vector.
         * @returns A Translation Matrix
         */
        static Matrix4 TranslationMatrix(const Vector3 &vector);
    };
} // namespace bde

#else
namespace bde {
    class Matrix4;
} // namespace bde
#endif /* defined(__BDEMath__Matrix4__) */
