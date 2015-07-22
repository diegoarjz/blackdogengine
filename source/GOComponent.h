#ifndef __BlackDogEngine__GOComponent__
#define __BlackDogEngine__GOComponent__

#include "Object.h"

namespace bde{
    class GameObject;
    typedef std::shared_ptr<GameObject> GameObjectPtr;
    typedef std::weak_ptr<GameObject> GameObjectWeakPtr;
    
    /**
     * Abstract class for a game object component
     */
    class GOComponent : public Object{
    protected:
        GameObjectWeakPtr mParentGameObject;
    public:
        RTTI_DECL

        /* ****************************
         * Construction & Destruction *
         * ***************************/
        GOComponent();
        virtual ~GOComponent();
        
        /* *******************
         * Getters & Setters *
         * ******************/
        void SetParentGameObject(GameObjectPtr go);
        GameObjectPtr GetParentGameObject() const;
//        virtual GOComponentTypes GetComponentType() const = 0;
        
        friend class GameObject;
    }; // class GOComponent
    
    typedef std::shared_ptr<GOComponent> GOComponentPtr;
    typedef std::weak_ptr<GOComponent> GOComponentWeakPtr;
} // namespace bde

#else
namespace bde{
    class GOComponent;
    typedef std::shared_ptr<GOComponent> GOComponentPtr;
    typedef std::weak_ptr<GOComponent> GOComponentWeakPtr;
} // namespace bde
#endif /* defined(__BlackDogEngine__GOComponent__) */
