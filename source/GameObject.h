#ifndef __BlackDogEngine__GameObject__
#define __BlackDogEngine__GameObject__

#include "Object.h"
#include "GOComponent.h"

#include "GOComponentTypeList.h"
#include "GOComponentHandle.h"

namespace bde{
    /**
     * The GameObject class implements a simple container for
     * Game Object Components. This class is also a messenger,
     * meaning that components can posts messages, communicating
     * with each other without knowing about their existence.
     * Messaging is the preffered method for inter game object
     * and inter component communication, as it improves decoupling.
     *
     * GameObjects do not own components, hence, they should not be destroyed in
     * the destructor. Each engine subsystem must destroy them.
     */
    class GameObject : public Object{
    private:
        GOComponentHandlePtr mComponents[GOComponentTypeList::componentCount];
        
        /// Indicates that the GO can be updated.
        bool mIsAlive;
    public:
        /* ****************************
         * Construction & Destruction *
         * ***************************/
        GameObject();
        virtual ~GameObject();

        void Kill();
        bool IsAlive() const;
        
        template<typename Subsystem_t, typename ComponentType>
        ComponentType* GetComponent(){
            auto compHandle = mComponents[ GOComponentTypeList::IndexOfType<ComponentType>() ];
            
            auto conv = std::dynamic_pointer_cast<GOComponentHandle<Subsystem_t, ComponentType>>( compHandle );
            auto comp = conv->GetComponent();
            
            return comp;
        }
        
        template<typename ComponentType>
        void SetComponent(GOComponentHandlePtr component){
            mComponents[ GOComponentTypeList::IndexOfType<ComponentType>() ] = component;
        }
        
    }; // class GameObject
} // namespace bde
#endif /* defined(__BlackDogEngine__GameObject__) */
