#ifndef __BlackDogEngine__TransformComponent__
#define __BlackDogEngine__TransformComponent__

#include <list>

#include "MathLib/MathLib.h"
#include "GOComponent.h"

namespace bde {
    
    class TransformComponent;
    typedef std::shared_ptr<TransformComponent> TransformComponentPtr;
    typedef std::weak_ptr<TransformComponent> TransformComponentWeakPtr;
    
    /**
     * Component that contains a transformation between
     * coordinate spaces.
     */
    class TransformComponent : public GOComponent{
    private:
        /// The parent of this transform.
        /// If it is null, then the parent
        /// transform is the world transform
        TransformComponentWeakPtr mParentTransform;
        /// The list of transforms whose parent is
        /// this transform
        std::list<TransformComponentWeakPtr> mChildren;
        
        /// Position relative to the parent transform.
        Vector3 mLocalPosition;
        /// Rotation relative to the parent transform.
        Quaternion mLocalRotation;
        /// Scale relative to the parent transform.
        Vector3 mLocalScale;
        
        /// The matrix that converts from local to world coordinates
        Matrix4 mLocalToWorld;
        /// The matrix that converst from world to local coordinates
        Matrix4 mWorldToLocal;
        
        /// Specifies if the mLocalToWorld matrix needs to be calculated
        bool mIsDirty;
        /// Specifies if the mWorldToLocal matrix needs to be calculated
        bool mInverseIsDirty;
        /// Specifies that this component has been updated since last frame
        bool mNeedsUpdate;
    public:
        RTTI_DECL;
        
        /* ****************************
         * Construction & Destruction *
         * ***************************/
        TransformComponent();
        virtual ~TransformComponent();
        
        virtual GOComponentTypes GetComponentType() const override;
        
        /* *******************
         * Getters & Setters *
         * ******************/
        /**
         * Sets the parent transform.
         * Null makes this transform a parent of the world transform.
         * @param parent [in] The parent transform.
         */
        void SetParentTransform(TransformComponentPtr parent);
        
        /**
         * Returns the parent transform.
         */
        TransformComponentPtr GetParentTransform();
        
        /**
         * Sets the local position. Sets dirty.
         * @param position [in] The new position.
         */
        void SetPosition(const Vector3 &position);
        /**
         * Sets the local position. Sets dirty.
         * @param x [in] New x coordinate.
         * @param y [in] New y coordinate.
         * @param z [in] New z coordinate.
         */
        void SetPosition(const float& x, const float& y, const float& z);
        /**
         * Sets the local position by translation. Sets dirty.
         * @param x [in] Translation in x coordinate.
         * @param y [in] Translation in y coordinate.
         * @param z [in] Translation in z coordinate.
         */
        void Translate(const float& x, const float& y, const float& z);
        /**
         * Sets the local position by translation. Sets dirty.
         * @param translation [in] Translation vector.
         */
        void Translate(const Vector3 &translation);
        /**
         * Returns the local position.
         * @return The local position.
         */
        Vector3 GetPosition() const;
        
        /**
         * Sets the local rotation. Sets dirty.
         * @param rotation [in] The new rotation.
         */
        void SetRotation(const Quaternion &rotation);
        /**
         * Rotates the local coordinate system around
         * local z axis by angle.
         * @param angle [in] Angle in radians.
         */
        void Yaw(const float& angle);
        /**
         * Rotates the local coordinate system around
         * local y axis by angle.
         * @param angle [in] Angle in radians.
         */
        void Pitch(const float& angle);
        /**
         * Rotates the local coordinate system around
         * local x axis by angle.
         * @param angle [in] Angle in radians.
         */
        void Roll(const float& angle);
        /**
         * Returns the local rotation.
         * @return The local rotation.
         */
        Quaternion GetRotation() const;
        /**
         * Sets the local scale. Sets dirty.
         * @param scale [in] The new scale.
         */
        void SetScale(const Vector3 &scale);
        /**
         * Set uniform scale. All of the scale components
         * are equal. Sets dirty.
         * @param scale [in] New uniform scale factor.
         */
        void SetScale(const float& scale);
        /**
         * Sets the local scale. Sets dirty.
         * @param x [in] Scale along x.
         * @param y [in] Scale along y.
         * @param z [in] Scale along z.
         */
        void SetScale(const float& x, const float& y, const float& z);
        /**
         * Returns the local scale.
         * @return The local scale.
         */
        Vector3 GetScale();
        
        /**
         * Calculates and returns the matrix that transforms this
         * into the parent coordinates.
         * @return 4x4 homogeneous matrix with the local to parent transform.
         */
        Matrix4 CalculateLocalToParentMatrix();
        
        /**
         * Calculates (if needed) and returns the matrix that transforms this
         * into the world coordinates. Modifies mLocalToWorld,
         * and unsets the dirty flag.
         *  @return 4x4 homogeneous matrix with the local to world transform.
         */
        Matrix4 GetLocalToWorldMatrix();
        
        /**
         * Calculates (if needed) and returns the matrix that transforms world
         * coordinates into this transform's coordinates. Modifies mWorldToLocal,
         * and unsusts the inverse dirty flag.
         * @return 4x4 homogeneous matrix with the world to local transform.
         */
        Matrix4 GetWorldToLocalMatrix();
        
        /**
         * Transforms a point from local coordinates into world coordinates.
         * @param localPoint [in] A point in local coordinates
         * @return A point in world coordinates
         */
        Vector3 TransformPointToWorldCoordinates(const Vector3 &localPoint);
        
        /**
         * Transforms a point from world coordinates into local coordinates.
         * @param worldPoint [in] A point in world cooridnates.
         * @return A point in local coordinates.
         */
        Vector3 TransformPointToLocalCoordinates(const Vector3 &worldPoint);
        
        /**
         * Transforms a direction from local coordinates into world coordinates.
         * @param localDirection [in] A direction in local coordinates.
         * @return A direction in world coordinates.
         */
        Vector3 TransformDirectionToWorldCoordinates(const Vector3 &localDirection);
        
        /**
         * Transforms a direction from world coordinates into local coordinates.
         * @param worldDirection [in] A direction in world coordinates.
         * @return A direction in local coordinates.
         */
        Vector3 TransformDirectionToLocalCoordinates(const Vector3 &worldDirection);
        
        bool NeedsUpdate() const;
    private:
        /**
         * Whenever any change that should be reflected on mLocalToWorld happens,
         * this should be called.
         */
        void setDirty();
    }; // class TransformComponent
} // namespace bde

#else
namespace bde{
    class TransformComponent;
    typedef std::shared_ptr<TransformComponent> TransformComponentPtr;
    typedef std::weak_ptr<TransformComponent> TransformComponentWeakPtr;
}
#endif /* defined(__BlackDogEngine__TransformComponent__) */
