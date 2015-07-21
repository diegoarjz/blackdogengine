#include "Transformation.h"

namespace bde{
    
    const Transformation Transformation::Identity;
    
    /* ****************************
     * Construction & Destruction *
     * ***************************/
    Transformation::Transformation(){
        
    }
    
    Transformation::Transformation(const Vector3 &eulerAngles, const Vector3 &pos, const Vector3 &scale){
        mPosition = pos;
        mScale = scale;
        mRotation = Quaternion::FromEulerAngles(eulerAngles);
        mHomogeneousMatrixCurrent = false;
    }
    
    Transformation::Transformation(const Transformation& other){
        mPosition = other.mPosition;
        mScale = other.mScale;
        mRotation = other.mRotation;
        mHomogeneousMatrixCurrent = false;
    }
    
    Transformation::~Transformation(){
        
    }
    
    /* *******************
     * Getters & Setters *
     * ******************/
    void Transformation::SetPosition(const float& x, const float& y, const float& z){
        SetPosition(Vector3(x,y,z));
    }
    
    void Transformation::SetPosition(const Vector3 &pos){
        mPosition = pos;
        mHomogeneousMatrixCurrent = false;
    }
    
    void Transformation::Translate(const float& x, const float& y, const float& z){
        Translate(Vector3(x,y,z));
        mHomogeneousMatrixCurrent = false;
    }
    
    void Transformation::Translate(const Vector3 &translation){
        mPosition += translation;
        mHomogeneousMatrixCurrent = false;
    }
    
    void Transformation::Yaw(const float& angle){
        mRotation = Quaternion::FromEulerAngles(Vector3(0,0,angle)) * mRotation;
        mHomogeneousMatrixCurrent = false;
    }
    
    void Transformation::Pitch(const float& angle){
        mRotation = Quaternion::FromEulerAngles(Vector3(angle,0,0)) * mRotation;
        mHomogeneousMatrixCurrent = false;
    }
    
    void Transformation::Roll(const float& angle){
        mRotation = Quaternion::FromEulerAngles(Vector3(0,angle,0)) * mRotation;
        mHomogeneousMatrixCurrent = false;
    }
    
    void Transformation::SetScale(const float& scale){
        mScale.X() = scale;
        mScale.Y() = scale;
        mScale.Z() = scale;
        mHomogeneousMatrixCurrent = false;
    }
    
    void Transformation::SetScale(const float& x, const float& y, const float& z){
        SetScale(Vector3(x,y,z));
        mHomogeneousMatrixCurrent = false;
    }
    
    void Transformation::SetScale(const Vector3 &s){
        mScale = s;
        mHomogeneousMatrixCurrent = false;
    }
    
    
    Vector3 Transformation::GetPosition()const{
        return mPosition;
    }
    
    Vector3 Transformation::GetScale()const{
        return mScale;
    }
    
    Quaternion Transformation::GetRotation()const{
        return mRotation;
    }
    
    void Transformation::SetRotation(const Quaternion& rot){
        mRotation = rot;
        mHomogeneousMatrixCurrent = false;
    }
    
    /* ***********
     * Operators *
     * **********/
    Transformation& Transformation::operator=(const Transformation& other){
        mRotation = other.mRotation;
        mScale = other.mScale;
        mPosition = other.mPosition;
        mHomogeneousMatrixCurrent = other.mHomogeneousMatrixCurrent;
        mHomogeneousMatrix = other.mHomogeneousMatrix;
        
        return *this;
    }
    
    bool Transformation::operator==(const Transformation &other){
        return  mPosition == other.mPosition &&
                mRotation == other.mRotation &&
                mScale == other.mScale;
    }
    
    bool Transformation::operator!=(const Transformation &other){
        return !(*this == other);
    }
    
    Transformation Transformation::operator*(const Transformation &t2){
        Transformation t;
        
        Matrix3 scaleMatrix(t2.mScale.X(), 0.0, 0.0,    // First Row
                            0.0, t2.mScale.Y(), 0.0,    // Second Row
                            0.0, 0.0, t2.mScale.Z()     // Third Row
                            );
        t.mPosition = t2.mRotation*(scaleMatrix*mPosition) + t2.mPosition;
        t.mScale = Vector3(mScale.X()*t.mScale.X(),
                           mScale.Y()*t.mScale.Y(),
                           mScale.Z()*t.mScale.Z());
        t.mRotation = t2.mRotation * mRotation;
        t.mHomogeneousMatrixCurrent = false;
        
        return t;
    }
    
    
} // namespace bde