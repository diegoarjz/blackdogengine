#include "Camera.h"

#include "TransformComponent.h"
#include "GameObject.h"
#include "MathLib/Rotation.h"

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
    Quaternionf Camera::GetOrientation(){
        return mParentGameObject.lock()->GetComponent<TransformComponent>()->GetRotation();
    }
    
    Vector3f Camera::GetPosition(){
        return mParentGameObject.lock()->GetComponent<TransformComponent>()->GetPosition();
    }
    
    Vector3f Camera::GetDirection(){
        return -1.0f*Matrix3f(Rotation<3, float>(GetOrientation())).GetCol(2);
    }
    
    Vector3f Camera::GetUp(){
        return Matrix3f(Rotation<3, float>(GetOrientation())).GetCol(1);
    }
    
    Vector3f Camera::GetRight(){
        return -1.0f*Matrix3f(Rotation<3, float>(GetOrientation())).GetCol(0);
    }
    
    void Camera::OnFrameChanged(){
        Vector3f pos = -1.0f*GetPosition();
        Matrix4f R = Inverse( Matrix4f(Rotation<4, float>(GetOrientation())) );
        Matrix4f T = Matrix4f({
            1,0,0,pos[0],
            0,1,0,pos[1],
            0,0,1,pos[2],
            0,0,0,1
        });
        
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
        mTop = tanf( fovAngle*GTE_C_DEG_TO_RAD *0.5 ) * nearPlane;
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
        mProjectionMatrix = Matrix4f({
            2*mNear/(mRight-mLeft),0,(mRight+mLeft)/(mRight-mLeft),0,
            0,2*mNear/(mTop-mBottom),(mTop+mBottom)/(mTop-mBottom),0,
            0,0,-(mFar+mNear)/(mFar-mNear),-(2*mNear*mFar)/(mFar-mNear),
            0,0,-1,0
        });
        
        // Need to recalculate the planes
        updatePlanes();
    }
}
