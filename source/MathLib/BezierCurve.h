//
//  BezierCurve.h
//  LinesLibrary
//
//  Created by Diego Jesus on 20/06/14.
//  Copyright (c) 2014 BlackDogEngine. All rights reserved.
//

#ifndef __LinesLibrary__BezierCurve__
#define __LinesLibrary__BezierCurve__

#include <iostream>
#include <vector>
#include "Matrix4.h"

namespace bde {
    class BezierCurve {
      public:
        enum BezierConstraints {
            /// The endpoints meet.
            G0,
            /// Tangent Vectors at the endpoints are colinear.
            G1,
            /// Tangent Vectors at the endpoints are colinear and have the same length.
            C1
        };

      private:
        static const Matrix4 sBaseMatrix;

        class BezierCurvePiece {
          private:
            BezierCurvePiece *mNextInChain;
            BezierCurvePiece *mPreviousInChain;

            BezierConstraints mConstraint;

            Matrix4 mControlPoints;
          public:

            /* ****************************
             * Construction & Destruction *
             * ***************************/
            BezierCurvePiece(const Vector4 &p1,
                             const Vector4 &p2,
                             const Vector4 &p3,
                             const Vector4 &p4,
                             BezierCurvePiece *previous = NULL);
            ~BezierCurvePiece();

            /* *********
             * Edition *
             * ********/
            void AddPiece(BezierCurvePiece *p);
            void SetControlPoint(const unsigned int &n, const Vector3 &pos);

            Vector4 GetPositionForT(const float &t);
            friend class BezierCurve;

          private:
            void setControlPointG0(const unsigned int &n, const Vector4 &pos);
            void setControlPointG1(const unsigned int &n, const Vector4 &pos);
            void setControlPointC1(const unsigned int &n, const Vector4 &pos);
        }; // class BezierCurvePiece

      private:
        std::vector<BezierCurvePiece *> mPieces;
        BezierConstraints mConstraint;
      public:

        /* ****************************
         * Construction & Destruction *
         * ***************************/
        BezierCurve(const Vector4 &p1,
                    const Vector4 &p2,
                    const Vector4 &p3,
                    const Vector4 &p4,
                    const BezierConstraints &constraint = G0);
        ~BezierCurve();

        Vector4 GetPositionForT(const float &T);

        std::vector<Vector4> GetControlPoints() const;

        void AppendPiece(const Vector4 &p1,
                         const Vector4 &p2,
                         const Vector4 &p3);
    }; // class BezierCurve
} // namespace bde

#else
namespace bde {
    class BezierCurvePiece;
    class BezierCurve;
} // namespace bde
#endif /* defined(__LinesLibrary__BezierCurve__) */
