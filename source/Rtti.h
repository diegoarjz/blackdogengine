//
//  Rtti.h
//  BlackDogEngine
//
//  Created by Diego Jesus on 10/1/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef BlackDogEngine_Rtti_h
#define BlackDogEngine_Rtti_h

#include <string>
#include <ostream>

namespace bde{
    /**
     * This class implements a Run-Time Type Information system with a single inheritance tree. All classes derived from Object
     * must have a static Rtti data member specifying the type. Used to know the object's class during runtime, allowing correct dynamic
     * casting.
     */
    class Rtti {
    private:
        /// This type name.
        std::string mName;
        /// The base type.
        const Rtti* mBaseType;
    public:
        /**
         * Constructor. baseType must not be null for all classes derived from Object, since Object is the root of the inheritance tree.
         * @param   name        [in] This type's name
         * @param   baseType    [in] The type from which this class is derived
         */
        Rtti(const std::string  &name, const Rtti* baseType);
        ~Rtti();
    
        /**
         * Returns this type's name.
         * @return  This type's name.
         */
        const std::string & GetName() const;
        /**
         * Indicates if it is an instance of this type or one of the types in the inheritance path.
         * @param   type    [in] The type to be checked
         * @return  true if both types share the same inheritance tree, false otherwise.
         */
        bool IsInstanceOf(const Rtti& type) const;
        /**
         * Indicates if both objects are exactly of the same type.
         * @param   type    [in] The type to be checked.
         * @return true if both types are the same, false otherwise
         */
        bool IsType(const Rtti& type) const;
        
        /**
         * Output operation, mainly for debugging purposes.
         * @param stream [in] Output stream.
         * @param o [in] Rtti to output.
         * @return The stream parameter, allowing to chain operations.
         */
        friend std::ostream& operator<< (std::ostream& stream, const Rtti& o);
    };
}
#else
namespace bde{
    class Rtti;
}
#endif
