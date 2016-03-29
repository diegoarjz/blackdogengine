// The contents of this file are based (in part or totally) in the
// source code authored by:
// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2016
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 2.1.0 (2016/01/25)

#pragma once

#include "Matrix.h"
#include "Vector2.h"

namespace bde
{

// Template alias for convenience.
template <typename Real>
using Matrix2 = Matrix<2, 2, Real>;
using Matrix2f = Matrix<2,2, float>;
using Matrix2d = Matrix<2,2, double>;


// Create a rotation matrix from an angle (in radians).  The matrix is
// [GTE_USE_MAT_VEC]
//   R(t) = {{c,-s},{s,c}}
// [GTE_USE_VEC_MAT]
//   R(t) = {{c,s},{-s,c}}
// where c = cos(t), s = sin(t), and the inner-brace pairs are rows of the
// matrix.
template <typename Real>
void MakeRotation(Real angle, Matrix2<Real>& rotation);

// Get the angle (radians) from a rotation matrix.  The caller is
// responsible for ensuring the matrix is a rotation.
template <typename Real>
Real GetRotationAngle(Matrix2<Real> const& rotation);

// Geometric operations.
template <typename Real>
Matrix2<Real> Inverse(Matrix2<Real> const& M,
    bool* reportInvertibility = nullptr);

template <typename Real>
Matrix2<Real> Adjoint(Matrix2<Real> const& M);

template <typename Real>
Real Determinant(Matrix2<Real> const& M);

template <typename Real>
Real Trace(Matrix2<Real> const& M);


template <typename Real>
void MakeRotation(Real angle, Matrix2<Real>& rotation)
{
    Real cs = cos(angle);
    Real sn = sin(angle);
#if defined(GTE_USE_MAT_VEC)
    rotation(0, 0) = cs;
    rotation(0, 1) = -sn;
    rotation(1, 0) = sn;
    rotation(1, 1) = cs;
#else
    rotation(0, 0) = cs;
    rotation(0, 1) = sn;
    rotation(1, 0) = -sn;
    rotation(1, 1) = cs;
#endif
}

template <typename Real>
Real GetRotationAngle(Matrix2<Real> const& rotation)
{
#if defined(GTE_USE_MAT_VEC)
    return atan2(rotation(1, 0), rotation(0, 0));
#else
    return atan2(rotation(0, 1), rotation(0, 0));
#endif
}

template <typename Real>
Matrix2<Real> Inverse(Matrix2<Real> const& M, bool* reportInvertibility)
{
    Matrix2<Real> inverse;
    bool invertible;
    Real det = M(0, 0)*M(1, 1) - M(0, 1)*M(1, 0);
    if (det != (Real)0)
    {
        Real invDet = ((Real)1) / det;
        inverse = Matrix2<Real>
        {
            M(1, 1)*invDet, -M(0, 1)*invDet,
                -M(1, 0)*invDet, M(0, 0)*invDet
        };
        invertible = true;
    }
    else
    {
        inverse.MakeZero();
        invertible = false;
    }

    if (reportInvertibility)
    {
        *reportInvertibility = invertible;
    }
    return inverse;
}

template <typename Real>
Matrix2<Real> Adjoint(Matrix2<Real> const& M)
{
    return Matrix2<Real>
    {
        M(1, 1), -M(0, 1),
            -M(1, 0), M(0, 0)
    };
}

template <typename Real>
Real Determinant(Matrix2<Real> const& M)
{
    Real det = M(0, 0)*M(1, 1) - M(0, 1)*M(1, 0);
    return det;
}

template <typename Real>
Real Trace(Matrix2<Real> const& M)
{
    Real trace = M(0, 0) + M(1, 1);
    return trace;
}


} // namespace bde
