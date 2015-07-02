#ifndef METATYPES_H_
#define METATYPES_H_

#include <iostream>

#include "../DataTypes.h"

namespace bde {
    /**
     * Defines information about a type.
     *
     * Provides other methods to convert between types.
     */
    struct MetaType {
        virtual const char *Name() const = 0;
        virtual size_t SizeOf() const = 0;
        virtual const std::string ToString(const void *v) const = 0;
        virtual const void FromString(const std::string &str, void *outValue) const = 0;
        virtual void Cast(void *to, const void *from, const MetaType &fromType) const {
            FromString( fromType.ToString(from), to );
        }
    };

    //
    // Bool Meta Type
    //
    struct BoolMetaType : public MetaType {
        virtual const char *Name() const override;
        virtual size_t SizeOf()const override;
        virtual const void FromString(const std::string &str, void *outValue)const override;
        virtual const std::string ToString(const void *v) const override;
    };
    const MetaType &GetMetaType(bool);
    
    // Numeric Meta Types
    const MetaType &GetMetaType(I16);
    const MetaType &GetMetaType(U16);
    
    const MetaType &GetMetaType(I32);
    const MetaType &GetMetaType(U32);
    
    const MetaType &GetMetaType(I64);
    const MetaType &GetMetaType(U64);
    
    const MetaType &GetMetaType(F32);
    const MetaType &GetMetaType(F64);

    //
    // Char* Meta Type
    //
    struct CharStarMetaType : public MetaType {
        virtual const char *Name()const override;
        virtual size_t SizeOf()const override;
        virtual const void FromString(const std::string &str, void *outValue) const override;
        virtual const std::string ToString(const void *v) const override;
    };
    const MetaType &GetMetaType(const char *);
    
    //
    // std::string Meta Type
    //
    struct StringMetaType : public MetaType {
        virtual const char *Name()const override;
        virtual size_t SizeOf()const override;
        virtual const void FromString(const std::string &str, void *outValue) const override;
        virtual const std::string ToString(const void *v) const override;
    };
    const MetaType &GetMetaType(std::string);
    
    //
    // Void Meta Type
    //
    struct VoidMetaType : public MetaType {
        virtual const char *Name() const override;
        virtual size_t SizeOf() const override;
        virtual const void FromString(const std::string &str, void *outValue)const override;
        virtual const std::string ToString(const void *v) const override;
    };
    const MetaType &GetMetaType(void);

    template<typename T>
    const MetaType &GetMetaTypeByType() {
        T t;
        return GetMetaType(t);
    }
    template<>
    const MetaType &GetMetaTypeByType<void>();

    //
    // Cast function
    //
    template<typename To>
    To Cast(const void *v, const MetaType &type) {
        To t;
        GetMetaType(t).Cast(&t, v, type);
        return t;
    }
    
    void PrintMetaType(const MetaType &type);
} // namespace bde
#else
namespace bde{
    struct MetaType;
}
#endif
