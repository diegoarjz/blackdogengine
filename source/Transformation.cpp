#include "Transformation.h"
#include "MathLib/Rotation.h"

namespace bde{
    
    const Transformation Transformation::Identity;
    
    /* ****************************
     * Construction & Destruction *
     * ***************************/
    Transformation::Transformation(){
        
    }
    
    Transformation::Transformation(const Vector3f &eulerAngles, const Vector3f &pos, const Vector3f &scale){
        mPosition = pos;
        mScale = scale;
        EulerAngles<float> e(0,1,2, eulerAngles[0],eulerAngles[1],eulerAngles[2]);
        Rotation<3, float> rot(e);
        mRotation = rot;
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
        SetPosition(Vector3f({x,y,z}));
    }
    
    void Transformation::SetPosition(const Vector3f &pos){
        mPosition = pos;
        mHomogeneousMatrixCurrent = false;
    }
    
    void Transformation::Translate(const float& x, const float& y, const float& z){
        Translate(Vector3f({x,y,z}));
        mHomogeneousMatrixCurrent = false;
    }
    
    void Transformation::Translate(const Vector3f &translation){
        mPosition = mPosition + translation;
        mHomogeneousMatrixCurrent = false;
    }
    
    void Transformation::Yaw(const float& angle){
        Quaternionf rot = Rotation<3, float>(EulerAngles<float>(0, 1, 2, 0, 0, angle));
        mRotation = rot * mRotation;
//        mRotation = Quaternionf::FromEulerAngles(Vector3f({0,0,angle})) * mRotation;
        mHomogeneousMatrixCurrent = false;
    }
    
    void Transformation::Pitch(const float& angle){
        Quaternionf rot = Rotation<3, float>(EulerAngles<float>(0, 1, 2, angle, 0, 0));
        mRotation = rot * mRotation;
//        mRotation = Quaternionf::FromEulerAngles(Vector3f({angle,0,0})) * mRotation;
        mHomogeneousMatrixCurrent = false;
    }
    
    void Transformation::Roll(const float& angle){
        Quaternionf rot = Rotation<3, float>(EulerAngles<float>(0, 1, 2, 0, angle, 0));
        mRotation = rot * mRotation;
//        mRotation = Quaternionf::FromEulerAngles(Vector3f({0,angle,0})) * mRotation;
        mHomogeneousMatrixCurrent = false;
    }
    
    void Transformation::SetScale(const float& scale){
        mScale[0] = scale;
        mScale[1] = scale;
        mScale[2] = scale;
        mHomogeneousMatrixCurrent = false;
    }
    
    void Transformation::SetScale(const float& x, const float& y, const float& z){
        SetScale(Vector3f({x,y,z}));
        mHomogeneousMatrixCurrent = false;
    }
    
    void Transformation::SetScale(const Vector3f &s){
        mScale = s;
        mHomogeneousMatrixCurrent = false;
    }
    
    
    Vector3f Transformation::GetPosition()const{
        return mPosition;
    }
    
    Vector3f Transformation::GetScale()const{
        return mScale;
    }
    
    Quaternionf Transformation::GetRotation()const{
        return mRotation;
    }
    
    void Transformation::SetRotation(const Quaternionf& rot){
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
        
        Matrix3f scaleMatrix({
            t2.mScale[0], 0.0, 0.0,    // First Row
            0.0, t2.mScale[1], 0.0,    // Second Row
            0.0, 0.0, t2.mScale[2]     // Third Row
        });
        auto scaledPosition = scaleMatrix*mPosition;
        Vector4f homogeneousScaledPosition({
            scaledPosition[0],scaledPosition[1],scaledPosition[2]
        });
        Vector4f homogenousT2Position({
            t2.mPosition[0],t2.mPosition[1],t2.mPosition[2]
        });
        auto homogeneousNewPosition = Rotate(t2.mRotation,homogeneousScaledPosition) + homogenousT2Position;
        t.mPosition = Vector3f({
            homogeneousNewPosition[0],homogeneousNewPosition[1],homogeneousNewPosition[2]
        }) / homogeneousNewPosition[3];
        t.mScale = Vector3f({
            mScale[0]*t.mScale[0],
            mScale[1]*t.mScale[1],
            mScale[2]*t.mScale[2]});
        t.mRotation = t2.mRotation * mRotation;
        t.mHomogeneousMatrixCurrent = false;
        
        return t;
    }
    
    
} // namespace bde