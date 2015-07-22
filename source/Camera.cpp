#include "Camera.h"

#include "TransformComponent.h"
#include "GameObject.h"

namespace bde{
    RTTI_DEF(Camera, "Camera", GOComponent);
    
    /* ****************************
     * Construction & Destruction *
     * ***************************/
    Camera::Camera(){
        //Frame
        mNumberOfCullingPlanes = 6;
        
        //Frustum
        SetFrustum(60, 1, 0.1, 100);
    }
    
    Camera::~Camera(){
    }
    
    /* *******
     * Frame *
     * ******/
    Quaternion Camera::GetOrientation(){
        return mParentGameObject.lock()->GetComponent<TransformComponent>()->GetRotation();
    }
    
    Vector3 Camera::GetPosition(){
        return mParentGameObject.lock()->GetComponent<TransformComponent>()->GetPosition();
    }
    
    Vector3 Camera::GetDirection(){
        return -1*Matrix3(GetOrientation()).GetColumn(2);
    }
    
    Vector3 Camera::GetUp(){
        return Matrix3(GetOrientation()).GetColumn(1);
    }
    
    Vector3 Camera::GetRight(){
        return Matrix3(GetOrientation()).GetColumn(0);
    }
    
    void Camera::OnFrameChanged(){
        Vector3 pos = -1*GetPosition();
        Matrix4 R = Matrix4(GetOrientation()).Inverse();
        Matrix4 T = Matrix4(1,0,0,pos.X(),
                            0,1,0,pos.Y(),
                            0,0,1,pos.Z(),
                            0,0,0,1);
        
        mViewMatrix = R*T;
        updatePlanes();
    }
    
    void Camera::updatePlanes(){
        
    }
    
    /* *********
     * Frustum *
     * ********/
    void Camera::SetFrustum(const float& left, const float& right, const float& top, const float& bottom, const float& nearPlane, const float& farPlane){
        mLeft = left;
        mRight = right;
        mTop = top;
        mBottom = bottom;
        mNear = nearPlane;
        mFar = farPlane;
        
        OnFrustumChanged();
    }
    
    void Camera::SetFrustum(const float& fovAngle, const float& aspectRatio, const float& nearPlane, const float& farPlane){
        mTop = tanf( MathUtils::ToRadians(fovAngle) *0.5 ) * nearPlane;
        mBottom = -mTop;
        mRight = aspectRatio * mTop;
        mLeft = -mRight;
        mNear = nearPlane;
        mFar = farPlane;
        
        OnFrustumChanged();
    }
    
    void Camera::GetFrustum(float &left, float &right, float &top, float &bottom, float &nearPlane, float &farPlane) const{
        left = mLeft;
        right = mRight;
        top = mTop;
        bottom = mBottom;
        nearPlane = mNear;
        farPlane = mFar;
    }
    
    void Camera::OnFrustumChanged(){
        mProjectionMatrix = Matrix4(2*mNear/(mRight-mLeft),0,(mRight+mLeft)/(mRight-mLeft),0,
                                    0,2*mNear/(mTop-mBottom),(mTop+mBottom)/(mTop-mBottom),0,
                                    0,0,-(mFar+mNear)/(mFar-mNear),-(2*mNear*mFar)/(mFar-mNear),
                                    0,0,-1,0);
        
        // Need to recalculate the planes
        updatePlanes();
    }
}