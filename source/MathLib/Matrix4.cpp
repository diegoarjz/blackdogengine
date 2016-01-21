//
//  Matrix4.cpp
//  BDEMath
//
//  Created by Diego Jesus on 29/04/14.
//  Copyright (c) 2014 BlackDogEngine. All rights reserved.
//

#include "Matrix4.h"
#include <glm/gtc/matrix_access.hpp>
#include <glm/gtx/euler_angles.hpp>

namespace bde {
    /* ****************************
     * Construction & Destruction *
     * ***************************/
    Matrix4::Matrix4():mMatrix(1) {
    }

    Matrix4::Matrix4(const Matrix4 &m) {
        mMatrix = m.mMatrix;
    }

    /**
     * Construct a matrix in the following format
     * | m00 m10 m20 m30 |
     * | m01 m11 m21 m31 |
     * | m02 m12 m22 m32 |
     * | m03 m13 m23 m33 |
     */
    Matrix4::Matrix4(const REAL &m00,const REAL &m10,const REAL &m20,
                     const REAL &m30,
                     const REAL &m01,const REAL &m11,const REAL &m21, const REAL &m31,
                     const REAL &m02,const REAL &m12,const REAL &m22, const REAL &m32,
                     const REAL &m03,const REAL &m13,const REAL &m23, const REAL &m33) {
        mMatrix = glm::mat4(m00, m01, m02, m03,
                            m10, m11, m12, m13,
                            m20, m21, m22, m23,
                            m30, m31, m32, m33);
    }

    /**
     * Constructs a matrix expanding the given Matrix3 in the following way
     * | m3 0 |
     * | 0  1 |
     */
    Matrix4::Matrix4(const Matrix3 &m3) {
        mMatrix = glm::mat4(m3.Get(0,0), m3.Get(1,0), m3.Get(2,0), 0,
                            m3.Get(0,1), m3.Get(1,1), m3.Get(2,1), 0,
                            m3.Get(0,2), m3.Get(1,2), m3.Get(2,2), 0,
                            0,           0,           0, 1);
    }

    Matrix4::Matrix4(const Quaternion &q){
        mMatrix = glm::toMat4(glm::quat(q.W(), q.X(), q.Y(), q.Z()));
    }
    
    Matrix4::~Matrix4() {
    }

#if GLM_COMPATIBLE == 1
    Matrix4::Matrix4(const glm::mat4 &m) {
        mMatrix = m;
    }

    Matrix4::operator glm::mat4() const {
        return mMatrix;
    }
#endif

    /* *******************
     * Getters & Setters *
     * ******************/
    Vector4<> Matrix4::GetColumn(const int &c) {
        return Vector4<>(glm::column(mMatrix, c));
    }

    void Matrix4::SetColumn(const int &index, const Vector4<> &c) {
        glm::vec4 v(c.X(), c.Y(), c.Z(), c.W());
        mMatrix = glm::column(mMatrix, index, v);
    }

    Vector4<> Matrix4::GetRow(const int &r) {
        return Vector4<>(glm::row(mMatrix, r));
    }

    void Matrix4::SetRow(const int &index, const Vector4<> &r) {
        glm::vec4 v(r.X(), r.Y(), r.Z(), r.W());
        mMatrix = glm::row(mMatrix, index, v);
    }

    REAL Matrix4::Get(const int &column, const int &row) const {
        return mMatrix[column][row];
    }

    void Matrix4::Set(const int &column, const int &row, const REAL &value) {
        mMatrix[column][row] = value;
    }

    /* ************
     * Operations *
     * ***********/
    Vector4<> Matrix4::operator*(const Vector4<> &v)const {
        return mMatrix*glm::vec4(v);
    }

    Matrix4 Matrix4::operator*(const Matrix4 &m)const {
        return Matrix4(mMatrix*m.mMatrix);
    }

    Matrix4 Matrix4::Inverse() const {
        Matrix4 m;
        m.mMatrix = glm::inverse(mMatrix);
        return m;
    }

    Matrix4 Matrix4::Transpose() const {
        Matrix4 m;
        m.mMatrix = glm::transpose(mMatrix);
        return m;
    }

    /* ****************
     * Static Methods *
     * ***************/
    Matrix4 Matrix4::ScaleMatrix(const float &x, const float &y, const float &z) {
        return Matrix4(x,0,0,0,
                       0,y,0,0,
                       0,0,z,0,
                       0,0,0,1);
    }

    Matrix4 Matrix4::FromEulerAnglesYXZ(const float &yaw, const float &pitch,
                                        const float &roll) {
        Matrix4 m;
        m.mMatrix = glm::eulerAngleYXZ(yaw, pitch, roll);
        return m;
    }

    Matrix4 Matrix4::TranslationMatrix(const float &x, const float &y,
                                       const float &z) {
        return Matrix4(1,0,0,x,
                       0,1,0,y,
                       0,0,1,z,
                       0,0,0,1);
    }

    Matrix4 Matrix4::TranslationMatrix(const Vector3<> &vector) {
        return Matrix4::TranslationMatrix(vector.X(), vector.Y(), vector.Z());
    }
    
    Matrix4 Matrix4::ScaleMatrix(const Vector3<> &scaleVector){
        return ScaleMatrix(scaleVector.X(),
                           scaleVector.Y(),
                           scaleVector.Z());
    }

    std::ostream &operator<< (std::ostream &o, const Matrix4 &m) {
        for(int i=0; i<4; ++i) {
            o << "| ";

            for(int j=0; j<4; ++j) {
                o << m.mMatrix[j][i] << " ";
            }

            o << "|" << std::endl;
        }

        return o;
    }
} // namespace bde