//
//  Matrix3.h
//  BDEMath
//
//  Created by Diego Jesus on 29/04/14.
//  Copyright (c) 2014 BlackDogEngine. All rights reserved.
//

#ifndef __BDEMath__Matrix3__
#define __BDEMath__Matrix3__

#include <iostream>
#include <glm/glm.hpp>
#include "MathLibConfigurations.h"
#include "Vector3.h"

namespace bde{
class Matrix3{
private:
    glm::mat3 mMatrix;
    
public:
    
    /* ****************************
     * Construction & Destruction *
     * ***************************/
    Matrix3();
    Matrix3(const Matrix3 &m);
    /**
     * Construct a matrix in the following format
     * | m00 m10 m20 |
     * | m01 m11 m21 |
     * | m02 m12 m22 |
     */
    Matrix3(const REAL &m00,const REAL &m10,const REAL &m20,
            const REAL &m01,const REAL &m11,const REAL &m21,
            const REAL &m02,const REAL &m12,const REAL &m22);
    ~Matrix3();
    
#if GLM_COMPATIBLE == 1
    Matrix3(const glm::mat3 &m);
    operator glm::mat3() const;
#endif
    
    /* *******************
     * Getters & Setters *
     * ******************/
    Vector3 GetColumn(const int &c) const;
    void SetColumn(const int &index, const Vector3 &c);
    
    Vector3 GetRow(const int &r) const;
    void SetRow(const int &index, const Vector3 &r);
    
    REAL Get(const int &column, const int &row) const;
    void Set(const int &column, const int &row, const REAL &value);
    
    /* ************
     * Operations *
     * ***********/
    Vector3 operator*(const Vector3 &v)const;
    Matrix3 operator*(const Matrix3 &m)const;
    bool operator==(const Matrix3 &m);
    bool operator!=(const Matrix3 &m);
    
    bool IsOrthogonal() const;
    
    friend std::ostream& operator<< (std::ostream& o, const Matrix3 &m);
};
} // namespace bde

#else

namespace bde{
    class Matrix3;
} // namespace bde

#endif /* defined(__BDEMath__Matrix3__) */
