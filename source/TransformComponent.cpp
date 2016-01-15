#include "TransformComponent.h"

namespace bde{
    RTTI_DEF(TransformComponent, "TransformComponent", GOComponent);
    
    /* ****************************
     * Construction & Destruction *
     * ***************************/
    TransformComponent::TransformComponent():mLocalScale(1,1,1){
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
    
    void TransformComponent::SetPosition(const Vector3<> &position){
        mLocalPosition = position;
        setDirty();
    }
    
    void TransformComponent::SetPosition(const float& x, const float& y, const float& z){
        SetPosition(Vector3<>(x,y,z));
    }
    
    void TransformComponent::Translate(const float& x, const float& y, const float& z){
        Translate(Vector3<>(x,y,z));
    }
    
    void TransformComponent::Translate(const Vector3<> &translation){
        mLocalPosition = mLocalPosition + translation;
        setDirty();
    }
    
    Vector3<> TransformComponent::GetPosition() const{
        return mLocalPosition;
    }
    
    void TransformComponent::SetRotation(const Quaternion &rotation){
        mLocalRotation = rotation;
        setDirty();
    }
    
    void TransformComponent::Yaw(const float& angle){
        mLocalRotation = Quaternion::FromEulerAngles(Vector3<>(0,0,angle)) * mLocalRotation;
        setDirty();
    }
    
    void TransformComponent::Pitch(const float& angle){
        mLocalRotation = Quaternion::FromEulerAngles(Vector3<>(angle,0,0)) * mLocalRotation;
        setDirty();
    }
    
    void TransformComponent::Roll(const float& angle){
        mLocalRotation = Quaternion::FromEulerAngles(Vector3<>(0,angle,0)) * mLocalRotation;
        setDirty();
    }
    
    Quaternion TransformComponent::GetRotation() const{
        return mLocalRotation;
    }
    
    void TransformComponent::SetScale(const Vector3<> &scale){
        mLocalScale = scale;
        setDirty();
    }
    
    void TransformComponent::SetScale(const float& scale){
        SetScale(Vector3<>(scale,scale,scale));
    }
    
    void TransformComponent::SetScale(const float& x, const float& y, const float& z){
        SetScale(Vector3<>(x,y,z));
    }
    
    Vector3<> TransformComponent::GetScale(){
        return mLocalScale;
    }
    
    Matrix4 TransformComponent::CalculateLocalToParentMatrix(){
        return  Matrix4::TranslationMatrix(mLocalPosition) *
                Matrix4(mLocalRotation) *
                Matrix4::ScaleMatrix(mLocalScale);
    }
    
    Matrix4 TransformComponent::GetLocalToWorldMatrix(){
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
    
    Matrix4 TransformComponent::GetWorldToLocalMatrix(){
        if(mInverseIsDirty){
            mWorldToLocal = GetLocalToWorldMatrix().Inverse();
            
            mInverseIsDirty = false;
        }
        
        return mWorldToLocal;
    }
    
    Vector3<> TransformComponent::TransformPointToWorldCoordinates(const Vector3<> &localPoint){
        Vector4 homogeneousTransformedPoint = GetLocalToWorldMatrix() *
                                              Vector4(localPoint.X(),
                                                      localPoint.Y(),
                                                      localPoint.Z(), 1.0f);
        
        homogeneousTransformedPoint = homogeneousTransformedPoint / homogeneousTransformedPoint.W();
        
        return Vector3<>(homogeneousTransformedPoint.X(),
                       homogeneousTransformedPoint.Y(),
                       homogeneousTransformedPoint.Z());
    }
    
    Vector3<> TransformComponent::TransformPointToLocalCoordinates(const Vector3<> &worldPoint){
        Vector4 homogeneousTransformedPoint = GetWorldToLocalMatrix() *
                                              glm::vec4(worldPoint.X(),
                                                        worldPoint.Y(),
                                                        worldPoint.Z(),
                                                        1.0f);
        homogeneousTransformedPoint = homogeneousTransformedPoint / homogeneousTransformedPoint.W();

        return Vector3<>(homogeneousTransformedPoint.X(),
                       homogeneousTransformedPoint.Y(),
                       homogeneousTransformedPoint.Z());
    }
    
    Vector3<> TransformComponent::TransformDirectionToWorldCoordinates(const Vector3<> &localDirection){
        // matrix multiply padding the extra element with a 0
        // notice that the worldToLocalMatrix is used here
        // and the point is multiplied as a row matrix before the
        // transform matrix.
        Vector4 homogeneousTransformedDirection = Vector4(localDirection.X(),
                                                          localDirection.Y(),
                                                          localDirection.Z(),
                                                          0.0f) * GetWorldToLocalMatrix();
        homogeneousTransformedDirection = homogeneousTransformedDirection / homogeneousTransformedDirection.W();
        return Vector3<>(homogeneousTransformedDirection.X(),
                         homogeneousTransformedDirection.Y(),
                         homogeneousTransformedDirection.Z());
    }
    
    Vector3<> TransformComponent::TransformDirectionToLocalCoordinates(const Vector3<> &worldDirection){
        Vector4 homogeneousTransformedDirection = Vector4(worldDirection.X(),
                                                          worldDirection.Y(),
                                                          worldDirection.Z(),
                                                          0.0f) * GetLocalToWorldMatrix();
        homogeneousTransformedDirection = homogeneousTransformedDirection / homogeneousTransformedDirection.W();
        return Vector3<>(homogeneousTransformedDirection.X(),
                         homogeneousTransformedDirection.Y(),
                         homogeneousTransformedDirection.Z());
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