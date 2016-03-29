// The contents of this file are based (in part or totally) in the
// source code authored by:
// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2016
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 2.1.0 (2016/01/25)

#pragma once

#include "../RangeIteration.h"
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>

// The SingularValueDecomposition class is an implementation of Algorithm
// 8.3.2 (The SVD Algorithm) described in "Matrix Computations, 2nd
// edition" by G. H. Golub and Charles F. Van Loan, The Johns Hopkins
// Press, Baltimore MD, Fourth Printing 1993.  Algorithm 5.4.2 (Householder
// Bidiagonalization) is used to reduce A to bidiagonal B.  Algorithm 8.3.1
// (Golub-Kahan SVD Step) is used for the iterative reduction from bidiagonal
// to diagonal.  If A is the original matrix, S is the matrix whose diagonal
// entries are the singular values, and U and V are corresponding matrices,
// then theoretically U^T*A*V = S.  Numerically, we have errors
// E = U^T*A*V - S.  Algorithm 8.3.2 mentions that one expects |E| is
// approximately u*|A|, where |M| denotes the Frobenius norm of M and where
// u is the unit roundoff for the floating-point arithmetic: 2^{-23} for
// 'float', which is FLT_EPSILON = 1.192092896e-7f, and 2^{-52} for'double',
// which is DBL_EPSILON = 2.2204460492503131e-16.
//
// The condition |a(i,i+1)| <= epsilon*(|a(i,i) + a(i+1,i+1)|) used to
// determine when the reduction decouples to smaller problems is implemented
// as:  sum = |a(i,i)| + |a(i+1,i+1)|; sum + |a(i,i+1)| == sum.  The idea is
// that the superdiagonal term is small relative to its diagonal neighbors,
// and so it is effectively zero.  The unit tests have shown that this
// interpretation of decoupling is effective.
//
// The condition |a(i,i)| <= epsilon*|B| used to determine when the
// reduction decouples (with a zero singular value) is implemented using
// the Frobenius norm of B and epsilon = multiplier*u, where for now the
// multiplier is hard-coded in Solve(...) as 8.
//
// The authors suggest that once you have the bidiagonal matrix, a practical
// implementation will store the diagonal and superdiagonal entries in linear
// arrays, ignoring the theoretically zero values not in the 2-band.  This is
// good for cache coherence, and we have used the suggestion.  The essential
// parts of the Householder u-vectors are stored in the lower-triangular
// portion of the matrix and the essential parts of the Householder v-vectors
// are stored in the upper-triangular portion of the matrix.  To avoid having
// to recompute 2/Dot(u,u) and 2/Dot(v,v) when constructing orthogonal U and
// V, we store these quantities in additional memory during bidiagonalization.
//
// For matrices with randomly generated values in [0,1], the unit tests
// produce the following information for N-by-N matrices.
//
// N  |A|     |E|        |E|/|A|    iterations
// -------------------------------------------
//  2  1.4831 4.1540e-16 2.8007e-16  1
//  3  2.1065 3.5024e-16 1.6626e-16  4
//  4  2.4979 7.4605e-16 2.9867e-16  6
//  5  3.6591 1.8305e-15 5.0025e-16  9
//  6  4.0572 2.0571e-15 5.0702e-16 10
//  7  4.7745 2.9057e-15 6.0859e-16 12
//  8  5.1964 2.7958e-15 5.3803e-16 13
//  9  5.7599 3.3128e-15 5.7514e-16 16
// 10  6.2700 3.7209e-15 5.9344e-16 16
// 11  6.8220 5.0580e-15 7.4142e-16 18
// 12  7.4540 5.2493e-15 7.0422e-16 21
// 13  8.1225 5.6043e-15 6.8997e-16 24
// 14  8.5883 5.8553e-15 6.8177e-16 26
// 15  9.1337 6.9663e-15 7.6270e-16 27
// 16  9.7884 9.1358e-15 9.3333e-16 29
// 17 10.2407 8.2715e-15 8.0771e-16 34
// 18 10.7147 8.9748e-15 8.3761e-16 33
// 19 11.1887 1.0094e-14 9.0220e-16 32
// 20 11.7739 9.7000e-15 8.2386e-16 35
// 21 12.2822 1.1217e-14 9.1329e-16 36
// 22 12.7649 1.1071e-14 8.6732e-16 37
// 23 13.3366 1.1271e-14 8.4513e-16 41
// 24 13.8505 1.2806e-14 9.2460e-16 43
// 25 14.4332 1.3081e-14 9.0637e-16 43
// 26 14.9301 1.4882e-14 9.9680e-16 46
// 27 15.5214 1.5571e-14 1.0032e-15 48
// 28 16.1029 1.7553e-14 1.0900e-15 49
// 29 16.6407 1.6219e-14 9.7467e-16 53
// 30 17.1891 1.8560e-14 1.0797e-15 55
// 31 17.7773 1.8522e-14 1.0419e-15 56
//
// The singularvalues and |E|/|A| values were compared to those generated by
// Mathematica Version 9.0; Wolfram Research, Inc., Champaign IL, 2012.
// The results were all comparable with singular values agreeing to a large
// number of decimal places.
//
// Timing on an Intel (R) Core (TM) i7-3930K CPU @ 3.20 GHZ (in seconds)
// for NxN matrices:
//
// N    |E|/|A|    iters bidiag  QR     U-and-V    comperr
// -------------------------------------------------------
//  512 3.8632e-15  848   0.341  0.016    1.844      2.203
// 1024 5.6456e-15 1654   4.279  0.032   18.765     20.844 
// 2048 7.5499e-15 3250  40.421  0.141  186.607    213.216
//
// where iters is the number of QR steps taken, bidiag is the computation
// of the Householder reflection vectors, U-and-V is the composition of
// Householder reflections and Givens rotations to obtain the orthogonal
// matrices of the decomposigion, and comperr is the computation E =
// U^T*A*V - S.

namespace bde
{

template <typename Real>
class SingularValueDecomposition
{
public:
    // The solver processes MxN symmetric matrices, where M >= N > 1
    // ('numRows' is M and 'numCols' is N) and the matrix is stored in
    // row-major order.  The maximum number of iterations ('maxIterations')
    // must be specified for the reduction of a bidiagonal matrix to a
    // diagonal matrix.  The goal is to compute MxM orthogonal U, NxN
    // orthogonal V, and MxN matrix S for which U^T*A*V = S.  The only
    // nonzero entries of S are on the diagonal; the diagonal entries are
    // the singular values of the original matrix.
    SingularValueDecomposition(int numRows, int numCols,
        unsigned int maxIterations);

    // A copy of the MxN input is made internally.  The order of the singular
    // values is specified by sortType: -1 (decreasing), 0 (no sorting), or +1
    // (increasing).  When sorted, the columns of the orthogonal matrices
    // are ordered accordingly.  The return value is the number of iterations
    // consumed when convergence occurred, 0xFFFFFFFF when convergence did not
    // occur or 0 when N <= 1 or M < N was passed to the constructor.
    unsigned int Solve(Real const* input, int sortType);

    // Get the singular values of the matrix passed to Solve(...).  The input
    // 'singularValues' must have N elements.
    void GetSingularValues(Real* singularValues) const;

    // Accumulate the Householder reflections, the Givens rotations, and the
    // diagonal fix-up matrix to compute the orthogonal matrices U and V for
    // which U^T*A*V = S.  The input uMatrix must be MxM and the input vMatrix
    // must be NxN, both stored in row-major order.
    void GetU(Real* uMatrix) const;
    void GetV(Real* vMatrix) const;

    // Compute a single column of U or V.  The reflections and rotations are
    // applied incrementally.  This is useful when you want only a small
    // number of the singular values or vectors.
    void GetUColumn(int index, Real* uColumn) const;
    void GetVColumn(int index, Real* vColumn) const;
    Real GetSingularValue(int index) const;

private:
    // Bidiagonalize using Householder reflections.  On input, mMatrix is a
    // copy of the input matrix and has one extra row.  On output, the
    // diagonal and superdiagonal contain the bidiagonalized results.  The
    // lower-triangular portion stores the essential parts of the Householder
    // u vectors (the elements of u after the leading 1-valued component) and
    // the upper-triangular portion stores the essential parts of the
    // Householder v vectors.  To avoid recomputing 2/Dot(u,u) and 2/Dot(v,v),
    // these quantities are stored in mTwoInvUTU and mTwoInvVTV.
    void Bidiagonalize();

    // A helper for generating Givens rotation sine and cosine robustly.
    void GetSinCos(Real u, Real v, Real& cs, Real& sn);

    // Test for (effectively) zero-valued diagonal entries (through all but
    // the last).  For each such entry, the B matrix decouples.  Perform
    // that decoupling.  If there are no zero-valued entries, then the
    // Golub-Kahan step must be performed.
    bool DiagonalEntriesNonzero(int imin, int imax, Real threshold);

    // This is Algorithm 8.3.1 in "Matrix Computations, 2nd edition" by
    // G. H. Golub and C. F. Van Loan.
    void DoGolubKahanStep(int imin, int imax);

    // The diagonal entries are not guaranteed to be nonnegative during the
    // construction.  After convergence to a diagonal matrix S, test for
    // negative entries and build a diagonal matrix that reverses the sign
    // on the S-entry.
    void EnsureNonnegativeDiagonal();

    // Sort the singular values and compute the corresponding permutation of
    // the indices of the array storing the singular values.  The permutation
    // is used for reordering the singular values and the corresponding
    // columns of the orthogonal matrix in the calls to GetSingularValues(...)
    // and GetOrthogonalMatrices(...).
    void ComputePermutation(int sortType);

    // The number rows and columns of the matrices to be processed.
    int mNumRows, mNumCols;

    // The maximum number of iterations for reducing the bidiagonal matrix
    // to a diagonal matrix.
    unsigned int mMaxIterations;

    // The internal copy of a matrix passed to the solver.  See the comments
    // about function Bidiagonalize() about what is stored in the matrix.
    std::vector<Real> mMatrix;  // MxN elements

    // After the initial bidiagonalization by Householder reflections, we no
    // longer need the full mMatrix.  Copy the diagonal and superdiagonal
    // entries to linear arrays in order to be cache friendly.
    std::vector<Real> mDiagonal;  // N elements
    std::vector<Real> mSuperdiagonal;  // N-1 elements

    // The Givens rotations used to reduce the initial bidiagonal matrix to
    // a diagonal matrix.  A rotation is the identity with the following
    // replacement entries:  R(index0,index0) = cs, R(index0,index1) = sn,
    // R(index1,index0) = -sn, and R(index1,index1) = cs.  If N is the
    // number of matrix columns and K is the maximum number of iterations, the
    // maximum number of right or left Givens rotations is K*(N-1).  The
    // maximum amount of memory is allocated to store these.  However, we also
    // potentially need left rotations to decouple the matrix when a diagonal
    // terms are zero.  Worst case is a number of matrices quadratic in N, so
    // for now we just use std::vector<Rotation> whose initial capacity is
    // K*(N-1).
    struct GivensRotation
    {
        GivensRotation();
        GivensRotation(int inIndex0, int inIndex1, Real inCs, Real inSn);
        int index0, index1;
        Real cs, sn;
    };

    std::vector<GivensRotation> mRGivens;
    std::vector<GivensRotation> mLGivens;

    // The diagonal matrix that is used to convert S-entries to nonnegative.
    std::vector<Real> mFixupDiagonal;  // N elements

    // When sorting is requested, the permutation associated with the sort is
    // stored in mPermutation.  When sorting is not requested, mPermutation[0]
    // is set to -1.  mVisited is used for finding cycles in the permutation.
    std::vector<int> mPermutation;  // N elements
    mutable std::vector<int> mVisited;  // N elements

    // Temporary storage to compute Householder reflections and to support
    // sorting of columns of the orthogonal matrices.
    std::vector<Real> mTwoInvUTU;  // N elements
    std::vector<Real> mTwoInvVTV;  // N-2 elements
    mutable std::vector<Real> mUVector;  // M elements
    mutable std::vector<Real> mVVector;  // N elements
    mutable std::vector<Real> mWVector;  // max(M,N) elements
};


template <typename Real>
SingularValueDecomposition<Real>::SingularValueDecomposition(int numRows,
    int numCols, unsigned int maxIterations)
    :
    mNumRows(0),
    mNumCols(0),
    mMaxIterations(0)
{
    if (numCols > 1 && numRows >= numCols && maxIterations > 0)
    {
        mNumRows = numRows;
        mNumCols = numCols;
        mMaxIterations = maxIterations;
        mMatrix.resize(numRows * numCols);
        mDiagonal.resize(numCols);
        mSuperdiagonal.resize(numCols - 1);
        mRGivens.reserve(maxIterations*(numCols - 1));
        mLGivens.reserve(maxIterations*(numCols - 1));
        mFixupDiagonal.resize(numCols);
        mPermutation.resize(numCols);
        mVisited.resize(numCols);
        mTwoInvUTU.resize(numCols);
        mTwoInvVTV.resize(numCols - 2);
        mUVector.resize(numRows);
        mVVector.resize(numCols);
        mWVector.resize(numRows);
    }
}

template <typename Real>
unsigned int SingularValueDecomposition<Real>::Solve(Real const* input,
    int sortType)
{
    if (mNumRows > 0)
    {
        int numElements = mNumRows * mNumCols;
        std::copy(input, input + numElements, mMatrix.begin());
        Bidiagonalize();

        // Compute 'threshold = multiplier*epsilon*|B|' as the threshold for
        // diagonal entries effectively zero; that is, |d| <= |threshold|
        // implies that d is (effectively) zero.  TODO: Allow the caller to
        // pass 'multiplier' to the constructor.
        //
        // We will use the L2-norm |B|, which is the length of the elements
        // of B treated as an NM-tuple.  The following code avoids overflow
        // when accumulating the squares of the elements when those elements
        // are large.
        Real maxAbsComp = std::abs(input[0]);
        for (int i = 1; i < numElements; ++i)
        {
            Real absComp = std::abs(input[i]);
            if (absComp > maxAbsComp)
            {
                maxAbsComp = absComp;
            }
        }

        Real norm = (Real)0;
        if (maxAbsComp > (Real)0)
        {
            Real invMaxAbsComp = ((Real)1) / maxAbsComp;
            for (int i = 0; i < numElements; ++i)
            {
                Real ratio = input[i] * invMaxAbsComp;
                norm += ratio * ratio;
            }
            norm = maxAbsComp*sqrt(norm);
        }

        Real const multiplier = (Real)8;  // TODO: Expose to caller.
        Real const epsilon = std::numeric_limits<Real>::epsilon();
        Real const threshold = multiplier * epsilon * norm;

        mRGivens.clear();
        mLGivens.clear();
        for (unsigned int j = 0; j < mMaxIterations; ++j)
        {
            int imin = -1, imax = -1;
            for (int i = mNumCols - 2; i >= 0; --i)
            {
                // When a01 is much smaller than its diagonal neighbors, it is
                // effectively zero.
                Real a00 = mDiagonal[i];
                Real a01 = mSuperdiagonal[i];
                Real a11 = mDiagonal[i + 1];
                Real sum = std::abs(a00) + std::abs(a11);
                if (sum + std::abs(a01) != sum)
                {
                    if (imax == -1)
                    {
                        imax = i;
                    }
                    imin = i;
                }
                else
                {
                    // The superdiagonal term is effectively zero compared to
                    // the neighboring diagonal terms.
                    if (imin >= 0)
                    {
                        break;
                    }
                }
            }

            if (imax == -1)
            {
                // The algorithm has converged.
                EnsureNonnegativeDiagonal();
                ComputePermutation(sortType);
                return j;
            }

            // We need to test diagonal entries of B for zero.  For each zero
            // diagonal entry, zero the superdiagonal.
            if (DiagonalEntriesNonzero(imin, imax, threshold))
            {
                // Process the lower-right-most unreduced bidiagonal block.
                DoGolubKahanStep(imin, imax);
            }
        }
        return 0xFFFFFFFF;
    }
    else
    {
        return 0;
    }
}

template <typename Real>
void SingularValueDecomposition<Real>::GetSingularValues(
    Real* singularValues) const
{
    if (singularValues && mNumCols > 0)
    {
        if (mPermutation[0] >= 0)
        {
            // Sorting was requested.
            for (int i = 0; i < mNumCols; ++i)
            {
                int p = mPermutation[i];
                singularValues[i] = mDiagonal[p];
            }
        }
        else
        {
            // Sorting was not requested.
            size_t numBytes = mNumCols*sizeof(Real);
            memcpy(singularValues, &mDiagonal[0], numBytes);
        }
    }
}

template <typename Real>
void SingularValueDecomposition<Real>::GetU(Real* uMatrix) const
{
    if (!uMatrix || mNumCols == 0)
    {
        // Invalid input or the constructor failed.
        return;
    }

    // Start with the identity matrix.
    std::fill(uMatrix, uMatrix + mNumRows*mNumRows, (Real)0);
    for (int d = 0; d < mNumRows; ++d)
    {
        uMatrix[d + mNumRows*d] = (Real)1;
    }

    // Multiply the Householder reflections using backward accumulation.
    int r, c;
    for (int i0 = mNumCols - 1, i1 = i0 + 1; i0 >= 0; --i0, --i1)
    {
        // Copy the u vector and 2/Dot(u,u) from the matrix.
        Real twoinvudu = mTwoInvUTU[i0];
        Real const* column = &mMatrix[i0];
        mUVector[i0] = (Real)1;
        for (r = i1; r < mNumRows; ++r)
        {
            mUVector[r] = column[mNumCols*r];
        }

        // Compute the w vector.
        mWVector[i0] = twoinvudu;
        for (r = i1; r < mNumRows; ++r)
        {
            mWVector[r] = (Real)0;
            for (c = i1; c < mNumRows; ++c)
            {
                mWVector[r] += mUVector[c] * uMatrix[r + mNumRows*c];
            }
            mWVector[r] *= twoinvudu;
        }

        // Update the matrix, U <- U - u*w^T.
        for (r = i0; r < mNumRows; ++r)
        {
            for (c = i0; c < mNumRows; ++c)
            {
                uMatrix[c + mNumRows*r] -= mUVector[r] * mWVector[c];
            }
        }
    }

    // Multiply the Givens rotations.
    for (auto const& givens : mLGivens)
    {
        int j0 = givens.index0;
        int j1 = givens.index1;
        for (r = 0; r < mNumRows; ++r, j0 += mNumRows, j1 += mNumRows)
        {
            Real& q0 = uMatrix[j0];
            Real& q1 = uMatrix[j1];
            Real prd0 = givens.cs * q0 - givens.sn * q1;
            Real prd1 = givens.sn * q0 + givens.cs * q1;
            q0 = prd0;
            q1 = prd1;
        }
    }

    if (mPermutation[0] >= 0)
    {
        // Sorting was requested.
        std::fill(mVisited.begin(), mVisited.end(), 0);
        for (c = 0; c < mNumCols; ++c)
        {
            if (mVisited[c] == 0 && mPermutation[c] != c)
            {
                // The item starts a cycle with 2 or more elements.
                int start = c, current = c, next;
                for (r = 0; r < mNumRows; ++r)
                {
                    mWVector[r] = uMatrix[c + mNumRows*r];
                }
                while ((next = mPermutation[current]) != start)
                {
                    mVisited[current] = 1;
                    for (r = 0; r < mNumRows; ++r)
                    {
                        uMatrix[current + mNumRows*r] =
                            uMatrix[next + mNumRows*r];
                    }
                    current = next;
                }
                mVisited[current] = 1;
                for (r = 0; r < mNumRows; ++r)
                {
                    uMatrix[current + mNumRows*r] = mWVector[r];
                }
            }
        }
    }
}

template <typename Real>
void SingularValueDecomposition<Real>::GetV(Real* vMatrix) const
{
    if (!vMatrix || mNumCols == 0)
    {
        // Invalid input or the constructor failed.
        return;
    }

    // Start with the identity matrix.
    std::fill(vMatrix, vMatrix + mNumCols*mNumCols, (Real)0);
    for (int d = 0; d < mNumCols; ++d)
    {
        vMatrix[d + mNumCols*d] = (Real)1;
    }

    // Multiply the Householder reflections using backward accumulation.
    int i0 = mNumCols - 3;
    int i1 = i0 + 1;
    int i2 = i0 + 2;
    int r, c;
    for (/**/; i0 >= 0; --i0, --i1, --i2)
    {
        // Copy the v vector and 2/Dot(v,v) from the matrix.
        Real twoinvvdv = mTwoInvVTV[i0];
        Real const* row = &mMatrix[mNumCols*i0];
        mVVector[i1] = (Real)1;
        for (r = i2; r < mNumCols; ++r)
        {
            mVVector[r] = row[r];
        }

        // Compute the w vector.
        mWVector[i1] = twoinvvdv;
        for (r = i2; r < mNumCols; ++r)
        {
            mWVector[r] = (Real)0;
            for (c = i2; c < mNumCols; ++c)
            {
                mWVector[r] += mVVector[c] * vMatrix[r + mNumCols*c];
            }
            mWVector[r] *= twoinvvdv;
        }

        // Update the matrix, V <- V - v*w^T.
        for (r = i1; r < mNumCols; ++r)
        {
            for (c = i1; c < mNumCols; ++c)
            {
                vMatrix[c + mNumCols*r] -= mVVector[r] * mWVector[c];
            }
        }
    }

    // Multiply the Givens rotations.
    for (auto const& givens : mRGivens)
    {
        int j0 = givens.index0;
        int j1 = givens.index1;
        for (c = 0; c < mNumCols; ++c, j0 += mNumCols, j1 += mNumCols)
        {
            Real& q0 = vMatrix[j0];
            Real& q1 = vMatrix[j1];
            Real prd0 = givens.cs * q0 - givens.sn * q1;
            Real prd1 = givens.sn * q0 + givens.cs * q1;
            q0 = prd0;
            q1 = prd1;
        }
    }

    // Fix-up the diagonal.
    for (r = 0; r < mNumCols; ++r)
    {
        for (c = 0; c < mNumCols; ++c)
        {
            vMatrix[c + mNumCols*r] *= mFixupDiagonal[c];
        }
    }

    if (mPermutation[0] >= 0)
    {
        // Sorting was requested.
        std::fill(mVisited.begin(), mVisited.end(), 0);
        for (c = 0; c < mNumCols; ++c)
        {
            if (mVisited[c] == 0 && mPermutation[c] != c)
            {
                // The item starts a cycle with 2 or more elements.
                int start = c, current = c, next;
                for (r = 0; r < mNumCols; ++r)
                {
                    mWVector[r] = vMatrix[c + mNumCols*r];
                }
                while ((next = mPermutation[current]) != start)
                {
                    mVisited[current] = 1;
                    for (r = 0; r < mNumCols; ++r)
                    {
                        vMatrix[current + mNumCols*r] =
                            vMatrix[next + mNumCols*r];
                    }
                    current = next;
                }
                mVisited[current] = 1;
                for (r = 0; r < mNumCols; ++r)
                {
                    vMatrix[current + mNumCols*r] = mWVector[r];
                }
            }
        }
    }
}

template <typename Real>
void SingularValueDecomposition<Real>::GetUColumn(int index,
    Real* uColumn) const
{
    if (0 <= index && index < mNumRows)
    {
        // y = H*x, then x and y are swapped for the next H
        Real* x = uColumn;
        Real* y = &mWVector[0];

        // Start with the Euclidean basis vector.
        memset(x, 0, mNumRows * sizeof(Real));
        if (index < mNumCols && mPermutation[0] >= 0)
        {
            // Sorting was requested.
            x[mPermutation[index]] = (Real)1;
        }
        else
        {
            x[index] = (Real)1;
        }

        // Apply the Givens rotations.
        for (auto const& givens : bde::reverse(mLGivens))
        {
            Real& xr0 = x[givens.index0];
            Real& xr1 = x[givens.index1];
            Real tmp0 = givens.cs * xr0 + givens.sn * xr1;
            Real tmp1 = -givens.sn * xr0 + givens.cs * xr1;
            xr0 = tmp0;
            xr1 = tmp1;
        }

        // Apply the Householder reflections.
        for (int c = mNumCols - 1; c >= 0; --c)
        {
            // Get the Householder vector u.
            int r;
            for (r = 0; r < c; ++r)
            {
                y[r] = x[r];
            }

            // Compute s = Dot(x,u) * 2/u^T*u.
            Real s = x[r];  // r = c, u[r] = 1
            for (int j = r + 1; j < mNumRows; ++j)
            {
                s += x[j] * mMatrix[c + mNumCols * j];
            }
            s *= mTwoInvUTU[c];

            // r = c, y[r] = x[r]*u[r] - s = x[r] - s because u[r] = 1
            y[r] = x[r] - s;

            // Compute the remaining components of y.
            for (++r; r < mNumRows; ++r)
            {
                y[r] = x[r] - s * mMatrix[c + mNumCols * r];
            }

            std::swap(x, y);
        }

        // The final product is stored in x.
        if (x != uColumn)
        {
            size_t numBytes = mNumRows*sizeof(Real);
            memcpy(uColumn, x, numBytes);
        }
    }
}

template <typename Real>
void SingularValueDecomposition<Real>::GetVColumn(int index,
    Real* vColumn) const
{
    if (0 <= index && index < mNumCols)
    {
        // y = H*x, then x and y are swapped for the next H
        Real* x = vColumn;
        Real* y = &mWVector[0];

        // Start with the Euclidean basis vector.
        memset(x, 0, mNumCols * sizeof(Real));
        if (mPermutation[0] >= 0)
        {
            // Sorting was requested.
            int p = mPermutation[index];
            x[p] = mFixupDiagonal[p];
        }
        else
        {
            x[index] = mFixupDiagonal[index];
        }

        // Apply the Givens rotations.
        for (auto const& givens : bde::reverse(mRGivens))
        {
            Real& xr0 = x[givens.index0];
            Real& xr1 = x[givens.index1];
            Real tmp0 = givens.cs * xr0 + givens.sn * xr1;
            Real tmp1 = -givens.sn * xr0 + givens.cs * xr1;
            xr0 = tmp0;
            xr1 = tmp1;
        }

        // Apply the Householder reflections.
        for (int r = mNumCols - 3; r >= 0; --r)
        {
            // Get the Householder vector v.
            int c;
            for (c = 0; c < r + 1; ++c)
            {
                y[c] = x[c];
            }

            // Compute s = Dot(x,v) * 2/v^T*v.
            Real s = x[c];  // c = r+1, v[c] = 1
            for (int j = c + 1; j < mNumCols; ++j)
            {
                s += x[j] * mMatrix[j + mNumCols * r];
            }
            s *= mTwoInvVTV[r];

            // c = r+1, y[c] = x[c]*v[c] - s = x[c] - s because v[c] = 1
            y[c] = x[c] - s;

            // Compute the remaining components of y.
            for (++c; c < mNumCols; ++c)
            {
                y[c] = x[c] - s * mMatrix[c + mNumCols * r];
            }

            std::swap(x, y);
        }

        // The final product is stored in x.
        if (x != vColumn)
        {
            size_t numBytes = mNumCols*sizeof(Real);
            memcpy(vColumn, x, numBytes);
        }
    }
}

template <typename Real>
Real SingularValueDecomposition<Real>::GetSingularValue(int index) const
{
    if (0 <= index && index < mNumCols)
    {
        if (mPermutation[0] >= 0)
        {
            // Sorting was requested.
            return mDiagonal[mPermutation[index]];
        }
        else
        {
            // Sorting was not requested.
            return mDiagonal[index];
        }
    }
    else
    {
        return (Real)0;
    }
}

template <typename Real>
void SingularValueDecomposition<Real>::Bidiagonalize()
{
    int r, c;
    for (int i = 0, ip1 = 1; i < mNumCols; ++i, ++ip1)
    {
        // Compute the U-Householder vector.
        Real length = (Real)0;
        for (r = i; r < mNumRows; ++r)
        {
            Real ur = mMatrix[i + mNumCols*r];
            mUVector[r] = ur;
            length += ur * ur;
        }
        Real udu = (Real)1;
        length = sqrt(length);
        if (length >(Real)0)
        {
            Real& u1 = mUVector[i];
            Real sgn = (u1 >= (Real)0 ? (Real)1 : (Real)-1);
            Real invDenom = ((Real)1) / (u1 + sgn * length);
            u1 = (Real)1;
            for (r = ip1; r < mNumRows; ++r)
            {
                Real& ur = mUVector[r];
                ur *= invDenom;
                udu += ur * ur;
            }
        }

        // Compute the rank-1 offset u*w^T.
        Real invudu = (Real)1 / udu;
        Real twoinvudu = invudu * (Real)2;
        for (c = i; c < mNumCols; ++c)
        {
            mWVector[c] = (Real)0;
            for (r = i; r < mNumRows; ++r)
            {
                mWVector[c] += mMatrix[c + mNumCols*r] * mUVector[r];
            }
            mWVector[c] *= twoinvudu;
        }

        // Update the input matrix.
        for (r = i; r < mNumRows; ++r)
        {
            for (c = i; c < mNumCols; ++c)
            {
                mMatrix[c + mNumCols*r] -= mUVector[r] * mWVector[c];
            }
        }

        if (i < mNumCols - 2)
        {
            // Compute the V-Householder vectors.
            length = (Real)0;
            for (c = ip1; c < mNumCols; ++c)
            {
                Real vc = mMatrix[c + mNumCols*i];
                mVVector[c] = vc;
                length += vc * vc;
            }
            Real vdv = (Real)1;
            length = sqrt(length);
            if (length >(Real)0)
            {
                Real& v1 = mVVector[ip1];
                Real sgn = (v1 >= (Real)0 ? (Real)1 : (Real)-1);
                Real invDenom = ((Real)1) / (v1 + sgn * length);
                v1 = (Real)1;
                for (c = ip1 + 1; c < mNumCols; ++c)
                {
                    Real& vc = mVVector[c];
                    vc *= invDenom;
                    vdv += vc * vc;
                }
            }

            // Compute the rank-1 offset w*v^T.
            Real invvdv = (Real)1 / vdv;
            Real twoinvvdv = invvdv * (Real)2;
            for (r = i; r < mNumRows; ++r)
            {
                mWVector[r] = (Real)0;
                for (c = ip1; c < mNumCols; ++c)
                {
                    mWVector[r] += mMatrix[c + mNumCols*r] * mVVector[c];
                }
                mWVector[r] *= twoinvvdv;
            }

            // Update the input matrix.
            for (r = i; r < mNumRows; ++r)
            {
                for (c = ip1; c < mNumCols; ++c)
                {
                    mMatrix[c + mNumCols*r] -= mWVector[r] * mVVector[c];
                }
            }

            mTwoInvVTV[i] = twoinvvdv;
            for (c = i + 2; c < mNumCols; ++c)
            {
                mMatrix[c + mNumCols*i] = mVVector[c];
            }
        }

        mTwoInvUTU[i] = twoinvudu;
        for (r = ip1; r < mNumRows; ++r)
        {
            mMatrix[i + mNumCols*r] = mUVector[r];
        }
    }

    // Copy the diagonal and subdiagonal for cache coherence in the
    // Golub-Kahan iterations.
    int k, ksup = mNumCols - 1, index = 0, delta = mNumCols + 1;
    for (k = 0; k < ksup; ++k, index += delta)
    {
        mDiagonal[k] = mMatrix[index];
        mSuperdiagonal[k] = mMatrix[index + 1];
    }
    mDiagonal[k] = mMatrix[index];
}

template <typename Real>
void SingularValueDecomposition<Real>::GetSinCos(Real x, Real y, Real& cs,
    Real& sn)
{
    // Solves sn*x + cs*y = 0 robustly.
    Real tau;
    if (y != (Real)0)
    {
        if (std::abs(y) > std::abs(x))
        {
            tau = -x / y;
            sn = ((Real)1) / sqrt(((Real)1) + tau*tau);
            cs = sn * tau;
        }
        else
        {
            tau = -y / x;
            cs = ((Real)1) / sqrt(((Real)1) + tau*tau);
            sn = cs * tau;
        }
    }
    else
    {
        cs = (Real)1;
        sn = (Real)0;
    }
}

template <typename Real>
bool SingularValueDecomposition<Real>::DiagonalEntriesNonzero(int imin,
    int imax, Real threshold)
{
    for (int i = imin; i <= imax; ++i)
    {
        if (std::abs(mDiagonal[i]) <= threshold)
        {
            // Use planar rotations to case the superdiagonal entry out of
            // the matrix, thus producing a row of zeros.
            Real x, z, cs, sn;
            Real y = mSuperdiagonal[i];
            mSuperdiagonal[i] = (Real)0;
            for (int j = i + 1; j <= imax + 1; ++j)
            {
                x = mDiagonal[j];
                GetSinCos(x, y, cs, sn);
                mLGivens.push_back(GivensRotation(i, j, cs, sn));
                mDiagonal[j] = cs*x - sn*y;
                if (j <= imax)
                {
                    z = mSuperdiagonal[j];
                    mSuperdiagonal[j] = cs*z;
                    y = sn*z;
                }
            }
            return false;
        }
    }
    return true;
}

template <typename Real>
void SingularValueDecomposition<Real>::DoGolubKahanStep(int imin, int imax)
{
    // The implicit shift.  Compute the eigenvalue u of the lower-right 2x2
    // block of A = B^T*B that is closer to b11.
    Real f0 = (imax >= (Real)1 ? mSuperdiagonal[imax - 1] : (Real)0);
    Real d1 = mDiagonal[imax];
    Real f1 = mSuperdiagonal[imax];
    Real d2 = mDiagonal[imax + 1];
    Real a00 = d1*d1 + f0*f0;
    Real a01 = d1*f1;
    Real a11 = d2*d2 + f1*f1;
    Real dif = (a00 - a11) * (Real)0.5;
    Real sgn = (dif >= (Real)0 ? (Real)1 : (Real)-1);
    Real a01sqr = a01 * a01;
    Real u = a11 - a01sqr / (dif + sgn*sqrt(dif*dif + a01sqr));
    Real x = mDiagonal[imin] * mDiagonal[imin] - u;
    Real y = mDiagonal[imin] * mSuperdiagonal[imin];

    Real a12, a21, a22, a23, cs, sn;
    Real a02 = (Real)0;
    int i0 = imin - 1, i1 = imin, i2 = imin + 1;
    for (/**/; i1 <= imax; ++i0, ++i1, ++i2)
    {
        // Compute the Givens rotation G and save it for use in computing
        // V in U^T*A*V = S.
        GetSinCos(x, y, cs, sn);
        mRGivens.push_back(GivensRotation(i1, i2, cs, sn));

        // Update B0 = B*G.
        if (i1 > imin)
        {
            mSuperdiagonal[i0] = cs*mSuperdiagonal[i0] - sn*a02;
        }

        a11 = mDiagonal[i1];
        a12 = mSuperdiagonal[i1];
        a22 = mDiagonal[i2];
        mDiagonal[i1] = cs*a11 - sn*a12;
        mSuperdiagonal[i1] = sn*a11 + cs*a12;
        mDiagonal[i2] = cs*a22;
        a21 = -sn*a22;

        // Update the parameters for the next Givens rotations.
        x = mDiagonal[i1];
        y = a21;

        // Compute the Givens rotation G and save it for use in computing
        // U in U^T*A*V = S.
        GetSinCos(x, y, cs, sn);
        mLGivens.push_back(GivensRotation(i1, i2, cs, sn));

        // Update B1 = G^T*B0.
        a11 = mDiagonal[i1];
        a12 = mSuperdiagonal[i1];
        a22 = mDiagonal[i2];
        mDiagonal[i1] = cs*a11 - sn*a21;
        mSuperdiagonal[i1] = cs*a12 - sn*a22;
        mDiagonal[i2] = sn*a12 + cs*a22;

        if (i1 < imax)
        {
            a23 = mSuperdiagonal[i2];
            a02 = -sn*a23;
            mSuperdiagonal[i2] = cs*a23;

            // Update the parameters for the next Givens rotations.
            x = mSuperdiagonal[i1];
            y = a02;
        }
    }
}

template <typename Real>
void SingularValueDecomposition<Real>::EnsureNonnegativeDiagonal()
{
    for (int i = 0; i < mNumCols; ++i)
    {
        if (mDiagonal[i] >= (Real)0)
        {
            mFixupDiagonal[i] = (Real)1;
        }
        else
        {
            mDiagonal[i] = -mDiagonal[i];
            mFixupDiagonal[i] = (Real)-1;
        }
    }
}

template <typename Real>
void SingularValueDecomposition<Real>::ComputePermutation(int sortType)
{
    if (sortType == 0)
    {
        // Set a flag for GetSingularValues() and GetOrthogonalMatrices() to
        // know that sorted output was not requested.
        mPermutation[0] = -1;
        return;
    }

    // Compute the permutation induced by sorting.  Initially, we start with
    // the identity permutation I = (0,1,...,N-1).
    struct SortItem
    {
        Real singularValue;
        int index;
    };

    std::vector<SortItem> items(mNumCols);
    int i;
    for (i = 0; i < mNumCols; ++i)
    {
        items[i].singularValue = mDiagonal[i];
        items[i].index = i;
    }

    if (sortType > 0)
    {
        std::sort(items.begin(), items.end(),
            [](SortItem const& item0, SortItem const& item1)
        {
            return item0.singularValue < item1.singularValue;
        }
        );
    }
    else
    {
        std::sort(items.begin(), items.end(),
            [](SortItem const& item0, SortItem const& item1)
        {
            return item0.singularValue > item1.singularValue;
        }
        );
    }

    i = 0;
    for (auto const& item : items)
    {
        mPermutation[i++] = item.index;
    }

    // GetOrthogonalMatrices() has nontrivial code for computing the
    // orthogonal U and V from the reflections and rotations.  To avoid
    // complicating the code further when sorting is requested, U and V are
    // computed as in the unsorted case.  We then need to swap columns of
    // U and V to be consistent with the sorting of the singular values.  To
    // minimize copying due to column swaps, we use permutation P.  The
    // minimum number of transpositions to obtain P from I is N minus the
    // number of cycles of P.  Each cycle is reordered with a minimum number
    // of transpositions; that is, the singular items are cyclically swapped,
    // leading to a minimum amount of copying.  For example, if there is a
    // cycle i0 -> i1 -> i2 -> i3, then the copying is
    //   save = singularitem[i0];
    //   singularitem[i1] = singularitem[i2];
    //   singularitem[i2] = singularitem[i3];
    //   singularitem[i3] = save;
}

template <typename Real>
SingularValueDecomposition<Real>::GivensRotation::GivensRotation()
{
    // No default initialization for fast creation of std::vector of objects
    // of this type.
}

template <typename Real>
SingularValueDecomposition<Real>::GivensRotation::GivensRotation(int inIndex0,
    int inIndex1, Real inCs, Real inSn)
    :
    index0(inIndex0),
    index1(inIndex1),
    cs(inCs),
    sn(inSn)
{
}


} // namespace bde