//
//  AABoundingBox.cpp
//  BDEMath
//
//  Created by Diego Jesus on 13/01/15.
//  Copyright (c) 2015 BlackDogEngine. All rights reserved.
//

#include "AABoundingBox.h"

namespace bde{
    /* ****************************
     * Construction & Destruction *
     * ***************************/
    AABoundingBox::AABoundingBox(){
        mBounds[0] = Vector3(0,0,0);
        mBounds[1] = Vector3(0,0,0);
        mIsNull = true;
    }
    
    AABoundingBox::AABoundingBox(const Vector3 &min, const Vector3 &max){
        mBounds[0] = min;
        mBounds[1] = max;
        mIsNull = false;
    }
    
    AABoundingBox::~AABoundingBox(){
        
    }
    
    /* *******************
     * Getters & Setters *
     * ******************/
    Vector3 AABoundingBox::GetPoint(const PointName &pointName) const{
        Vector3 point = mBounds[0];
        int p = (int)pointName;
        
        if(p & 0x1){
            point.X() = mBounds[1].X();
        }
        
        if(p & 0x2){
            point.Y() = mBounds[1].Y();
        }
        
        if(p & 0x4){
            point.Z() = mBounds[1].Z();
        }
        
        return point;
    }
    
    void AABoundingBox::GetPoints(Vector3 *points){
        for(int i=0; i<8; ++i){
            points[i] = GetPoint((PointName)i);
        }
    }
    
    REAL AABoundingBox::SizeX() const{
        return mBounds[1].X() - mBounds[0].X();
    }
    
    REAL AABoundingBox::SizeY() const{
        return mBounds[1].Y() - mBounds[0].Y();
    }
    
    REAL AABoundingBox::SizeZ() const{
        return mBounds[1].Z() - mBounds[0].Z();
    }
    
    bool AABoundingBox::IsNull() const{
        return mIsNull;
    }
    
    void AABoundingBox::SetNull(const bool &null){
        mIsNull = null;
    }
    
    void AABoundingBox::GrowToContain(const Vector3 &point){
        if(point.X() < mBounds[0].X())
            mBounds[0].X() = point.X();
        if(point.Y() < mBounds[0].Y())
            mBounds[0].Y() = point.Y();
        if(point.Z() < mBounds[0].Z())
            mBounds[0].Z() = point.Z();
        
        if(point.X() > mBounds[1].X())
            mBounds[1].X() = point.X();
        if(point.Y() > mBounds[1].Y())
            mBounds[1].Y() = point.Y();
        if(point.Z() > mBounds[1].Z())
            mBounds[1].Z() = point.Z();
    }
        
}