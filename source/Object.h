#ifndef BlackDogEngine_Object_h
#define BlackDogEngine_Object_h

#include <map>
#include <memory>
#include <string>

#include "DataTypes.h"
#include "Rtti.h"

namespace bde {
    class Object;
    typedef std::shared_ptr<Object> ObjectPtr;  ///< Defines the type for smart pointers to objects.
    typedef U32                     uid_t;      ///< Defines the type for object's unique ids as a 32 bit unsigned integer.
    
    /**
     * Base class for the Object System. Has a generated unique ID (UID) and a user defined name.
     * Each class derived class must have a different Run-time Type Information static instance,
     * creating a single inheritance tree. Although C++ offers multiple inheritance, the 
     * Object System in the Black Dog Engine does not allow.
     * 
     * @author  Diego Jesus
     * @date    2011
     */
    class Object : public std::enable_shared_from_this<Object>{
    private:        
        static uid_t sNextUID;  ///< Next generated UID.

        uid_t       mUID;       ///< The Object's UID.
        std::string mName;      ///< User assigned name (via SetName)
    public:
        /* ***************************
         * Run Time Type Information *
         * **************************/
        /// Run-Time Type Information for this object.
        static const Rtti TYPE;
        /**
         * Returns the RTTI for this object. All classes derived from Object must implement this method.
         * @return The RTTI for this object.
         */
        virtual const Rtti& GetType() const {return TYPE;}
        
        /**
         * Indicates if this Object is exactly an instance of the class indicated in type.
         * @param   type    The RTTI type to be checked against.
         * @return  true if this instance is of type, false otherwise.
         */
        bool IsType(const Rtti& type) const;
        /**
         * Indicates if this Object is an instance of type or one of the types in its inheritance tree.
         * @param   type  The RTTI type to be checked against.
         * @return  true if type is in this object inheritance tree, false otherwise
         */
        bool IsInstanceOf(const Rtti& type) const;
        
        /**
         * Indicates if this Object is of the exactly same class as the Object passed as argument.
         * @param   o   The other Object to be checked against.
         * @return  true if both objects are instances of the same class, false otherwise
         */
        bool IsType(const Object* o) const;
        /**
         *  Indicates if this Object's RTTI belongs to the same inheritance tree as o
         * @param   o   The other Object to be checked against.
         * @return  true if both objects share the same inheritance tree.
         */
        bool IsInstanceOf(const Object* o) const;
        
        /**
         * Statically cast this Object to another type. The new class must be towards the root of this object's inheritance tree.
         * @return The casted object.
         */
        template <class T> 
        static T* StaticCast(Object *o){
            return (T*)o;
        }
        
        /**
         * Statically cast this Object to another type. The new class must be towards the root of this object's inheritance tree.
         * @return The casted object.
         */
        template <class T> 
        static const T* StaticCast(const Object *o){
            return (T*)o;
        }
        
        /**
         * Dynamically cast this Object to another type.
         * @return The casted object.
         */
        template <class T> 
        static T* DynamicCast(Object *o){
            return (o && o->IsInstanceOf(T::TYPE)) ? (T*)o : NULL;
        }
        
        /**
         * Dynamically cast this Object to another type.
         * @return The casted object.
         */
        template <class T> 
        static const T* DynamicCast(const Object *o){
            return (o && o->IsInstanceOf(T::TYPE)) ? (T*)o : NULL;
        }
        
        /* ****************
         * Object Methods *
         * ****************/
        /* **************
         * Constructors *
         * *************/
        /**
         * Default constructor. Generates its UID and adds itself to the mapping between UIDs and Objects.
         */
        Object();
        
        /* ***********************
         * Object Identification *
         * **********************/
        /**
         * Sets this object's name.
         * @param   name    The object's new name
         */
        void SetName(const std::string& name);
        /**
         * Returns this object's name.
         * @return The object's name
         */
        const std::string& GetName()const;
        
        /**
         * Returns this object's UID
         * @return The Object's UID
         */
        uid_t GetUID() const;
        
        /**
         * Searches inside this object for another object with the specified name. Sub classes should
         * implement this method.
         * @param   name    The name of the object to search for.
         * @return  The object if found, NULL otherwise
         */
        virtual ObjectPtr Search(const std::string& name);
        
        /**
         * Searches inside this object for another object with the specified UID. Sub classes should
         * implement this method.
         * @param   name    The UID of the object to search for.
         * @return  The object if found, NULL otherwise
         */
        virtual ObjectPtr Search(uid_t UID);
        
        /**
         * Creates a string tree for this object and all its contained objects. Used for debug purposes
         * @param   indentation
         * @return  A formatted string with all the objects contained in this object.
         */
        virtual std::string StringTree(U16 indentation=0);
        
        /**
         * Returns a std::string containg this Object's information. Object derived classes should implement this method.
         * @return  A std::string with this Object's information.
         */
        virtual std::string ToString() const;

        
        /**
         * Output operation, mainly for debugging purposes.
         * @param stream [in] Output stream.
         * @param o [in] Object to output.
         * @return The stream parameter, allowing to chain operations.
         */
        friend std::ostream& operator<< (std::ostream& stream, const Object& o);
        
        /* ************
         * Destructor *
         * ***********/
        virtual ~Object();
    };
}

#else
namespace bde{
    class Object;
    typedef std::shared_ptr<Object> ObjectPtr;  ///< Defines the type for smart pointers to objects.
    typedef U32                     uid_t;      ///< Defines the type for object's unique ids as a 32 bit unsigned integer.
}
#endif
