#ifndef __BlackDogEngine__GameObject__
#define __BlackDogEngine__GameObject__

#include "Object.h"
#include "GOComponent.h"

#include "GOComponentTypeList.h"

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
        GOComponentPtr mComponents[GOComponentTypeList::componentCount];
        
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
        
        /**
         * Based on the type of the component (in template parameters), 
         * this function calculates the component index on the component array,
         * casts it into the correct type and returns it.
         *
         * @see GOComponentTypeList
         */
        template<typename ComponentType>
        std::shared_ptr<ComponentType> GetComponent(){
            auto compHandle = mComponents[ GOComponentTypeList::IndexOfType<ComponentType>() ];
            auto comp = std::dynamic_pointer_cast<ComponentType>( compHandle );
            return comp;
        }
        
        template<typename ComponentType>
        void SetComponent(std::shared_ptr<ComponentType> component){
            mComponents[ GOComponentTypeList::IndexOfType<ComponentType>() ] = component;
            component->SetParentGameObject( std::dynamic_pointer_cast<GameObject>( shared_from_this() ) );
        }
        
    }; // class GameObject
} // namespace bde
#endif /* defined(__BlackDogEngine__GameObject__) */
