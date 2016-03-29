#include "TransformComponent.h"
#include "MathLib/Rotation.h"
#include "MathLib/translation_matrix.h"
#include "MathLib/scale_matrix.h"

namespace bde{
    RTTI_DEF(TransformComponent, "TransformComponent", GOComponent);
    
    /* ****************************
     * Construction & Destruction *
     * ***************************/
    TransformComponent::TransformComponent():mLocalScale({1,1,1}){
        mIsDirty = true;
        mInverseIsDirty = true;
        mNeedsUpdate = true;
    }
    
    TransformComponent::~TransformComponent(){
        
    }
    
    /* *******************
     * Getters & Setters *
     * ******************/
    void TransformComponent::SetParentTransform(TransformComponentPtr parent){
        
        if(!mParentTransform.expired()){
            mParentTransform.lock()->mChildren.remove_if([parent](TransformComponentWeakPtr c){
                return c.lock() == parent;
            });
        }
        
        if(parent != nullptr){
            TransformComponentWeakPtr this_ptr = std::dynamic_pointer_cast<TransformComponent>(shared_from_this());
            parent->mChildren.push_back(this_ptr);
        }
        
        mParentTransform = parent;
    }
    
    TransformComponentPtr TransformComponent::GetParentTransform(){
        return mParentTransform.lock();
    }
    
    void TransformComponent::SetPosition(const Vector3f &position){
        mLocalPosition = position;
        setDirty();
    }
    
    void TransformComponent::SetPosition(const float& x, const float& y, const float& z){
        SetPosition(Vector3f({x,y,z}));
    }
    
    void TransformComponent::Translate(const float& x, const float& y, const float& z){
        Translate(Vector3f({x,y,z}));
    }
    
    void TransformComponent::Translate(const Vector3f &translation){
        mLocalPosition = mLocalPosition + translation;
        setDirty();
    }
    
    Vector3f TransformComponent::GetPosition() const{
        return mLocalPosition;
    }
    
    void TransformComponent::SetRotation(const Quaternionf &rotation){
        mLocalRotation = rotation;
        setDirty();
    }
    
    void TransformComponent::Yaw(const float& angle){
        Quaternionf rot = Rotation<3, float>(EulerAngles<float>(0, 1, 2, 0, 0, angle));
        mLocalRotation = rot * mLocalRotation;
//        mLocalRotation = Quaternionf::FromEulerAngles(Vector3f(0,0,angle)) * mLocalRotation;
        setDirty();
    }
    
    void TransformComponent::Pitch(const float& angle){
        Quaternionf rot = Rotation<3, float>(EulerAngles<float>(0, 1, 2, angle, 0, 0));
        mLocalRotation = rot * mLocalRotation;
//        mLocalRotation = Quaternionf::FromEulerAngles(Vector3f(angle,0,0)) * mLocalRotation;
        setDirty();
    }
    
    void TransformComponent::Roll(const float& angle){
        Quaternionf rot = Rotation<3, float>(EulerAngles<float>(0, 1, 2, 0, angle, 0));
        mLocalRotation = rot * mLocalRotation;
//        mLocalRotation = Quaternionf::FromEulerAngles(Vector3f(0,angle,0)) * mLocalRotation;
        setDirty();
    }
    
    Quaternionf TransformComponent::GetRotation() const{
        return mLocalRotation;
    }
    
    void TransformComponent::SetScale(const Vector3f &scale){
        mLocalScale = scale;
        setDirty();
    }
    
    void TransformComponent::SetScale(const float& scale){
        SetScale(Vector3f({scale,scale,scale}));
    }
    
    void TransformComponent::SetScale(const float& x, const float& y, const float& z){
        SetScale(Vector3f({x,y,z}));
    }
    
    Vector3f TransformComponent::GetScale(){
        return mLocalScale;
    }
    
    Matrix4f TransformComponent::CalculateLocalToParentMatrix(){
        return  translation_matrix(mLocalPosition) *
                Matrix4f(Rotation<4, float>(mLocalRotation)) *
                scale_matrix(mLocalScale);
    }
    
    Matrix4f TransformComponent::GetLocalToWorldMatrix(){
        if(mIsDirty){
            if(mParentTransform.expired()){
                mLocalToWorld = CalculateLocalToParentMatrix();
            }
            else{
                mLocalToWorld = mParentTransform.lock()->GetLocalToWorldMatrix() * CalculateLocalToParentMatrix();
            }
            
            mIsDirty = false;
        }
        
        return mLocalToWorld;
    }
    
    Matrix4f TransformComponent::GetWorldToLocalMatrix(){
        if(mInverseIsDirty){
            mWorldToLocal = Inverse( GetLocalToWorldMatrix() );
            
            mInverseIsDirty = false;
        }
        
        return mWorldToLocal;
    }
    
    Vector3f TransformComponent::TransformPointToWorldCoordinates(const Vector3f &localPoint){
        Vector4f homogeneousTransformedPoint = GetLocalToWorldMatrix() *
                                                Vector4f({
                                                    localPoint[0],
                                                    localPoint[1],
                                                    localPoint[2], 1.0f
                                                });
        
        homogeneousTransformedPoint = homogeneousTransformedPoint / homogeneousTransformedPoint[3];
        
        return Vector3f({
            homogeneousTransformedPoint[0],
            homogeneousTransformedPoint[1],
            homogeneousTransformedPoint[2]
        });
    }
    
    Vector3f TransformComponent::TransformPointToLocalCoordinates(const Vector3f &worldPoint){
        Vector4f homogeneousTransformedPoint = GetWorldToLocalMatrix() *
                                               Vector4f({worldPoint[0],
                                                        worldPoint[1],
                                                        worldPoint[2],
                                                        1.0f});
        homogeneousTransformedPoint = homogeneousTransformedPoint / homogeneousTransformedPoint[3];

        return Vector3f({homogeneousTransformedPoint[0],
                        homogeneousTransformedPoint[1],
                        homogeneousTransformedPoint[2]});
    }
    
    Vector3f TransformComponent::TransformDirectionToWorldCoordinates(const Vector3f &localDirection){
        // matrix multiply padding the extra element with a 0
        // notice that the worldToLocalMatrix is used here
        // and the point is multiplied as a row matrix before the
        // transform matrix.
        Vector4f homogeneousTransformedDirection = Vector4f({localDirection[0],
                                                          localDirection[1],
                                                          localDirection[2],
                                                          0.0f}) * GetWorldToLocalMatrix();
        homogeneousTransformedDirection = homogeneousTransformedDirection / homogeneousTransformedDirection[3];
        return Vector3f({homogeneousTransformedDirection[0],
                         homogeneousTransformedDirection[1],
                        homogeneousTransformedDirection[2]});
    }
    
    Vector3f TransformComponent::TransformDirectionToLocalCoordinates(const Vector3f &worldDirection){
        Vector4f homogeneousTransformedDirection = Vector4f({worldDirection[0],
                                                            worldDirection[1],
                                                            worldDirection[2],
                                                            0.0f}) * GetLocalToWorldMatrix();
        homogeneousTransformedDirection = homogeneousTransformedDirection / homogeneousTransformedDirection[3];
        return Vector3f({homogeneousTransformedDirection[0],
                        homogeneousTransformedDirection[1],
                        homogeneousTransformedDirection[2]});
    }
    
    void TransformComponent::setDirty(){
        if(!mIsDirty){
            mIsDirty = true;
            mInverseIsDirty = true;
            
            for(auto child : mChildren){
                child.lock()->setDirty();
            }
        }
        mNeedsUpdate = true;
    }

    bool TransformComponent::NeedsUpdate() const{
        return mNeedsUpdate;
    }
} // namespace bde
