//
//  Matrix3.cpp
//  BDEMath
//
//  Created by Diego Jesus on 29/04/14.
//  Copyright (c) 2014 BlackDogEngine. All rights reserved.
//

#include "Matrix3.h"
#include <glm/gtc/matrix_access.hpp>

namespace bde {
    /* ****************************
     * Construction & Destruction *
     * ***************************/
    Matrix3::Matrix3():mMatrix(1) {
    }

    Matrix3::Matrix3(const Matrix3 &m) {
        mMatrix = m.mMatrix;
    }

    Matrix3::Matrix3(const REAL &m00,const REAL &m10,const REAL &m20,
                     const REAL &m01,const REAL &m11,const REAL &m21,
                     const REAL &m02,const REAL &m12,const REAL &m22) {
        mMatrix = glm::mat3(m00, m01, m02,
                            m10, m11, m12,
                            m20, m21, m22);
    }
    
    Matrix3::Matrix3(const Quaternion &q){
        mMatrix = glm::toMat3((glm::quat)q);
    }

    Matrix3::~Matrix3() {
    }

#if GLM_COMPATIBLE == 1
    Matrix3::Matrix3(const glm::mat3 &m) {
        mMatrix = m;
    }

    Matrix3::operator glm::mat3() const {
        return mMatrix;
    }
#endif

    /* *******************
     * Getters & Setters *
     * ******************/
    Vector3f Matrix3::GetColumn(const int &c) const {
        return Vector3f(glm::column(mMatrix, c));
    }

    void Matrix3::SetColumn(const int &index, const Vector3f &c) {
        mMatrix = glm::column(mMatrix, index, c);
    }

    Vector3f Matrix3::GetRow(const int &r) const {
        return Vector3f(glm::row(mMatrix, r));
    }

    void Matrix3::SetRow(const int &index, const Vector3f &r) {
        mMatrix = glm::row(mMatrix, index, r);
    }

    REAL Matrix3::Get(const int &column, const int &row) const {
        return mMatrix[column][row];
    }

    void Matrix3::Set(const int &column, const int &row, const REAL &value) {
        mMatrix[column][row] = value;
    }

    /* ************
     * Operations *
     * ***********/
    Vector3f Matrix3::operator*(const Vector3f &v)const {
        return mMatrix*glm::vec3(v);
    }

    Matrix3 Matrix3::operator*(const Matrix3 &m)const {
        return Matrix3(mMatrix*m.mMatrix);
    }

    bool Matrix3::operator==(const Matrix3 &m) {
        return mMatrix == m.mMatrix;
    }

    bool Matrix3::operator!=(const Matrix3 &m) {
        return !(*this == m);
    }

    bool Matrix3::IsOrthogonal() const {
        // Check each row against the others.
        for(int i=0; i<3; ++i) {
            Vector3f row1 = GetRow(i);

            // If the row is not normalized
            if(row1.Length() != 1) {
                return false;
            }

            // If they're not orthogonal to the other rows
            for(int j=i; j<3; ++j) {
                if(i==j) {
                    continue;
                }

                Vector3f row2 = GetRow(j);

                if(row1.Dot(row2) != 0) {
                    return false;
                }
            }
        }

        // Check each column against the others.
        for(int i=0; i<3; ++i) {
            Vector3f col1 = GetColumn(i);

            // If the row is not normalized
            if(col1.Length() != 1) {
                return false;
            }

            // If they're not orthogonal to the other rows
            for(int j=i; j<3; ++j) {
                if(i==j) {
                    continue;
                }

                Vector3f col2 = GetColumn(j);

                if(col1.Dot(col2) != 0) {
                    return false;
                }
            }
        }

        return true;
    }

    std::ostream &operator<< (std::ostream &o, const Matrix3 &m) {
        for(int i=0; i<3; ++i) {
            o << "| ";

            for(int j=0; j<3; ++j) {
                o << m.mMatrix[j][i] << " ";
            }

            o << "|" << std::endl;
        }

        return o;
    }

} // namespace bde