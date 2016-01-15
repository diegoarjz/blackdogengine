#ifndef CAMERA_H_
#define CAMERA_H_

#include "GOComponent.h"

#include "MathLib/MathLib.h"

namespace bde{
    class CameraSystem;
    /**
     * This class defines a projection camera.
     * By default, it is placed on the world origin.
     * The direction vector points towards the negative Z.
     * The right vector points to the positive X.
     * The up vector points to the positive Y.
     * Therefore, the default rotation matrix (actually the quaternion) is the following:
     *  [ 1 0 0 ]
     *  [ 0 1 0 ]
     *  [ 0 0 1 ]
     * where the first column contains the right vector, the second the up vector and the
     * third the negative direction vector.
     */
    class Camera : public GOComponent{
    public:
        // Viewport
        //        ViewportPtr mViewport;
        
        // Frustum
        /// Distance to the near plane
        float mNear;
        /// Distance to the far plane
        float mFar;
        /// Coordinates of the intersection of the left clipping plane with the near plane.
        float mLeft;
        /// Coordinates of the intersection of the right clipping plane with the near plane.
        float mRight;
        /// Coordinates of the intersection of the top clipping plane with the near plane.
        float mTop;
        /// Coordinates of the intersection of the bottom clipping plane with the near plane.
        float mBottom;
        
        enum{
            CAM_FRUSTUM_PLANES = 6,
            MAX_CULLING_PLANES = 6
        };
        
        enum{
            PLANE_LEFT,
            PLANE_RIGHT,
            PLANE_BOTTOM,
            PLANE_TOP,
            PLANE_NEAR,
            PLANE_FAR
        };
        
        Matrix4 mProjectionMatrix;
        Matrix4 mViewMatrix;
    private:
        U8 mNumberOfCullingPlanes;
        Plane mCullingPlanes[MAX_CULLING_PLANES];
        Plane mLocalPlanes[MAX_CULLING_PLANES];
    public:
        RTTI_DECL;
        
        /* ****************************
         * Construction & Destruction *
         * ***************************/
        Camera();
        virtual ~Camera();
        
        /* *******
         * Frame *
         * ******/
        Quaternion GetOrientation();
        Vector3<> GetDirection();
        Vector3<> GetUp();
        Vector3<> GetRight();
        Vector3<> GetPosition();
        
        void OnFrameChanged();
        
        inline Matrix4 GetViewMatrix() { return mViewMatrix;}
        
        /* *********
         * Frustum *
         * ********/
        void SetFrustum(const float& left, const float& right, const float& top, const float& bottom, const float& nearPlane, const float& farPlane);
        void SetFrustum(const float& fovAngle, const float& aspectRatio, const float& near, const float& far);
        void GetFrustum(float &left, float &right, float &top, float &bottom, float &nearPlane, float &farPlane) const;
        void OnFrustumChanged();
        
        inline Matrix4 GetProjectionMatrix() { return mProjectionMatrix; }
        
    protected:
        virtual void updatePlanes();
    };
    
    typedef std::shared_ptr<Camera> CameraPtr;
    
} // namespace bde

#else
namespace bde{
    class Camera;
}

#endif