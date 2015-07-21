#include "GOComponent.h"

namespace bde {
    RTTI_DEF(GOComponent, "GOComponent", Object);
    
    /* ****************************
     * Construction & Destruction *
     * ***************************/
    GOComponent::GOComponent(){
        
    }
    
    GOComponent::~GOComponent(){
        
    }
    
    /* *******************
     * Getters & Setters *
     * ******************/
    void GOComponent::SetParentGameObject(GameObjectPtr go){
        mParentGameObject = go;
    }
    
    GameObjectPtr GOComponent::GetParentGameObject() const{
        return mParentGameObject.lock();
    }
}