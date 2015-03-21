//
//  BezierCurve.cpp
//  LinesLibrary
//
//  Created by Diego Jesus on 20/06/14.
//  Copyright (c) 2014 BlackDogEngine. All rights reserved.
//

#include "BezierCurve.h"

#include <math.h>

namespace bde{
    
    const Matrix4 BezierCurve::sBaseMatrix = Matrix4(-1,3,-3,1,
                                                     3,-6,3,0,
                                                     -3,3,0,0,
                                                     1,0,0,0);
    
    /* ****************************
     * Construction & Destruction *
     * ***************************/
    BezierCurve::BezierCurvePiece::BezierCurvePiece(const Vector4 &p1,
                                                    const Vector4 &p2,
                                                    const Vector4 &p3,
                                                    const Vector4 &p4,
                                                    BezierCurve::BezierCurvePiece *previous){
        
        mPreviousInChain = previous;
        mNextInChain = NULL;
        
        mControlPoints.SetRow(0, p1);
        mControlPoints.SetRow(1, p2);
        mControlPoints.SetRow(2, p3);
        mControlPoints.SetRow(3, p4);
    }
    
    BezierCurve::BezierCurvePiece::~BezierCurvePiece(){
        if(mNextInChain != NULL)
            delete mNextInChain;
    }
    
    /* *********
     * Edition *
     * ********/
    void BezierCurve::BezierCurvePiece::AddPiece(BezierCurve::BezierCurvePiece *p){
        if(mNextInChain != NULL){
            mNextInChain->AddPiece(p);
        }
        else{
            mNextInChain = p;
            p->mPreviousInChain = this;
        }
        
        Vector4 pos3 = mControlPoints.GetRow(2);
        SetControlPoint(2, Vector3(pos3.X(), pos3.Y(), pos3.Z()));
    }
    
    void BezierCurve::BezierCurvePiece::SetControlPoint(const unsigned int &n, const Vector3 &pos){
        if(n > 3)
            return;
        
        Vector4 newControlPoint(pos.X(), pos.Y(), pos.Z(), 1);
        
        switch (mConstraint) {
            case G0:
                setControlPointG0(n, newControlPoint);
                break;
            case G1:
                setControlPointG1(n, newControlPoint);
                break;
            case C1:
                setControlPointC1(n, newControlPoint);
                break;
        }
    }
    
    void BezierCurve::BezierCurvePiece::setControlPointG0(const unsigned int &n, const Vector4 &pos){
        mControlPoints.SetRow(n, pos);
    }
    
    void BezierCurve::BezierCurvePiece::setControlPointG1(const unsigned int &n, const Vector4 &pos){
        if(n == 0){
            Vector4 currentControlPoint = mControlPoints.GetRow(0);
            Vector4 translation = pos-currentControlPoint;
            
            if(mPreviousInChain != NULL){
                Vector4 previousNewPosition = mPreviousInChain->mControlPoints.GetRow(2) + translation;
                mPreviousInChain->mControlPoints.SetRow(2, translation);
                
                mPreviousInChain->mControlPoints.SetRow(3, pos);
            }
            
            return;
        }
        
        if(n == 1){
            mControlPoints.SetRow(1, pos);
            
            if(mPreviousInChain != NULL){
                Vector4 previousPieceControlPoint2 = mPreviousInChain->mControlPoints.GetRow(2);
                float previousControlPointLength = (pos-previousPieceControlPoint2).Length();
                
                Vector4 tangent = mControlPoints.GetRow(0) - pos;
                tangent.Normalize();
                
                Vector4 previousNewControlPoint = mControlPoints.GetRow(0)+previousControlPointLength*tangent;
                mPreviousInChain->mControlPoints.SetRow(2, previousNewControlPoint);
            }
            
            return;
        }
        
        if(n == 2){
            mControlPoints.SetRow(2, pos);
            
            if(mNextInChain != NULL){
                Vector4 nextPieceControlPoint1 = mNextInChain->mControlPoints.GetRow(1);
                float nextControlPointLength = (pos-nextPieceControlPoint1).Length();
                
                Vector4 tangent = mControlPoints.GetRow(3) - pos;
                tangent.Normalize();
                
                Vector4 nextNewControlPoint = mControlPoints.GetRow(3)+nextControlPointLength*tangent;
                mNextInChain->mControlPoints.SetRow(1, nextNewControlPoint);
            }
            
            return;
        }
        
        if(n == 3){
            Vector4 currentControlPoint = mControlPoints.GetRow(3);
            Vector4 translation = pos-currentControlPoint;
            
            if(mNextInChain != NULL){
                Vector4 nextNewPosition = mNextInChain->mControlPoints.GetRow(1) + translation;
                mNextInChain->mControlPoints.SetRow(1, nextNewPosition);
                
                mNextInChain->mControlPoints.SetRow(0, pos);
            }
            
            return;
        }
    }
    
    void BezierCurve::BezierCurvePiece::setControlPointC1(const unsigned int &n, const Vector4 &pos){
        if(n == 0){
            Vector4 currentControlPoint = mControlPoints.GetRow(0);
            Vector4 translation = pos-currentControlPoint;
            
            if(mPreviousInChain != NULL){
                Vector4 previousNewPosition = mPreviousInChain->mControlPoints.GetRow(2) + translation;
                mPreviousInChain->mControlPoints.SetRow(2, translation);
                
                mPreviousInChain->mControlPoints.SetRow(3, pos);
            }
            
            return;
        }
        
        if(n == 1){
            mControlPoints.SetRow(1, pos);
            
            if(mPreviousInChain != NULL){
                Vector4 previousPieceControlPoint2 = mPreviousInChain->mControlPoints.GetRow(2);
                float previousControlPointLength = (pos-mControlPoints.GetRow(0)).Length();
                
                Vector4 tangent = mControlPoints.GetRow(0) - pos;
                tangent.Normalize();
                
                Vector4 previousNewControlPoint = mControlPoints.GetRow(0)+previousControlPointLength*tangent;
                mPreviousInChain->mControlPoints.SetRow(2, previousNewControlPoint);
            }
            
            return;
        }
        
        if(n == 2){
            mControlPoints.SetRow(2, pos);
            
            if(mNextInChain != NULL){
                Vector4 nextPieceControlPoint1 = mNextInChain->mControlPoints.GetRow(1);
                float nextControlPointLength = (pos-mControlPoints.GetRow(3)).Length();
                
                Vector4 tangent = mControlPoints.GetRow(3) - pos;
                tangent.Normalize();
                
                Vector4 nextNewControlPoint = mControlPoints.GetRow(3)+nextControlPointLength*tangent;
                mNextInChain->mControlPoints.SetRow(1, nextNewControlPoint);
            }
            
            return;
        }
        
        if(n == 3){
            Vector4 currentControlPoint = mControlPoints.GetRow(3);
            Vector4 translation = pos-currentControlPoint;
            
            if(mNextInChain != NULL){
                Vector4 nextNewPosition = mNextInChain->mControlPoints.GetRow(1) + translation;
                mNextInChain->mControlPoints.SetRow(1, nextNewPosition);
                
                mNextInChain->mControlPoints.SetRow(0, pos);
            }
            
            return;
        }
    }
    
    Vector4 BezierCurve::BezierCurvePiece::GetPositionForT(const float &t){
        Vector4 T(t*t*t, t*t, t, 1);
        
        return T*(sBaseMatrix*mControlPoints);
    }
    
    /* ****************************
     * Construction & Destruction *
     * ***************************/
    BezierCurve::BezierCurve(const Vector4 &p1,
                             const Vector4 &p2,
                             const Vector4 &p3,
                             const Vector4 &p4,
                             const BezierConstraints &constraint){
        
        BezierCurvePiece *piece = new BezierCurvePiece(p1,p2,p3,p4, NULL);
        mConstraint = constraint;
        piece->mConstraint = mConstraint;
        mPieces.push_back(piece);
    }
    
    BezierCurve::~BezierCurve(){
        delete mPieces.front();
    }
    
    void BezierCurve::AppendPiece(const Vector4 &p2,
                                  const Vector4 &p3,
                                  const Vector4 &p4){
        
        BezierCurvePiece *lastPiece = mPieces.back();
        Vector4 p1 = lastPiece->mControlPoints.GetRow(3);
        BezierCurvePiece *newPiece = new BezierCurvePiece(p1,p2,p3,p4,lastPiece);
        newPiece->mConstraint = mConstraint;
        lastPiece->AddPiece(newPiece);
        mPieces.push_back(newPiece);
    }
    
    Vector4 BezierCurve::GetPositionForT(const float &t){
        float pieceNum = floorf(t);
        float pieceT = t-pieceNum;
        if(pieceNum == mPieces.size()){
            pieceNum--;
            pieceT=1;
        }
        return mPieces[pieceNum]->GetPositionForT(pieceT);
    }
    
    std::vector<Vector4> BezierCurve::GetControlPoints() const{
        std::vector<Vector4> points;
        
        for(int i=0; i<mPieces.size(); ++i){
            BezierCurvePiece *p = mPieces[i];
            points.push_back(p->mControlPoints.GetRow(0));
            points.push_back(p->mControlPoints.GetRow(1));
            points.push_back(p->mControlPoints.GetRow(2));
        }
        
        points.push_back( mPieces.back()->mControlPoints.GetRow(3));
        
        return points;
    }
} // namespace bde
