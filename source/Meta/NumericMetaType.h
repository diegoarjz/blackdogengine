#ifndef NUMERICDATATYPE_H_
#define NUMERICDATATYPE_H_

#include <stdio.h>

#include "../DataTypes.h"

#include "MetaType.h"
#include "TypeList.h"

namespace bde {
    
    /**
     * Templated meta types for numeric types.
     */
    template<typename T>
    struct NumericMetaType : public MetaType{
        virtual const char *Name() const override;
        
        virtual size_t SizeOf()const override{
            return sizeof(T);
        }
        
        virtual const void FromString(const std::string &str, void *outValue)const override{
            *(T *)outValue = std::atof(str.c_str());
        }
        
        virtual const std::string ToString(const void *v) const override{
            return std::to_string( *(T *)v );
        }
    }; // class NumericMetaType

    
    
} // namespace bde
#endif
