//
//  MetaType.cpp
//  BlackDogEngine
//
//  Created by Diego Jesus on 19/06/15.
//
//

#include "MetaType.h"
#include "NumericMetaType.h"
#include "../DataTypes.h"

namespace bde {
    
    void PrintMetaType(const MetaType &type) {
        std::cout << "Type Name: " << type.Name() << "\n";
        std::cout << "     Size: " << type.SizeOf() << std::endl;
    }
    
    //
    // bool Meta Type
    //
    struct BoolMetaType gBoolMetaType;
    
    const char* BoolMetaType::Name() const{
        return "bool";
    }
    size_t BoolMetaType::SizeOf()const{
        return sizeof(bool);
    }
    const void BoolMetaType::FromString(const std::string &str, void *outValue)const{
        *(bool *)outValue = (str == "true");
    }
    const std::string BoolMetaType::ToString(const void *v) const {
        return ((*(bool *)v) ? "true" : "false");
    }
    
    const MetaType &GetMetaType(bool) {
        return gBoolMetaType;
    }
    
    //
    // char* MetaType
    //
    struct CharStarMetaType gCharStarMetaType;
    
    const char* CharStarMetaType::Name()const{
        return "char*";
    }
    size_t CharStarMetaType::SizeOf()const{
        return sizeof(char *);
    }
    const void CharStarMetaType::FromString(const std::string &str, void *outValue) const {
        char *ptr = (char *)outValue;
        
        for(int i=0; i<str.size(); ++i) {
            ptr[i] = str[i];
        }
        
        ptr[str.size()] = 0;
    }
    const std::string CharStarMetaType::ToString(const void *v) const {
        return *(char **)v;
    }
    
    const MetaType &GetMetaType(const char *) {
        return gCharStarMetaType;
    }
    
    //
    // String MetaType
    //
    struct StringMetaType gStringMetaType;
    
    const char* StringMetaType::Name()const{
        return "string";
    }
    size_t StringMetaType::SizeOf()const{
        return sizeof(char *);
    }
    const void StringMetaType::FromString(const std::string &str, void *outValue) const {
        *(std::string *)outValue = str;
    }
    const std::string StringMetaType::ToString(const void *v) const {
        return *(std::string *)v;
    }
    
    const MetaType &GetMetaType(std::string) {
        return gStringMetaType;
    }
    
    //
    // integer Meta Types
    //
    struct NumericMetaType<U16> gUShortIntMetaType;
    const MetaType &GetMetaType(U16) {
        return gUShortIntMetaType;
    }
    
    struct NumericMetaType<I16> gShortIntMetaType;
    const MetaType &GetMetaType(I16) {
        return gShortIntMetaType;
    }
    
    struct NumericMetaType<U32> gUIntMetaType;
    const MetaType &GetMetaType(U32) {
        return gUIntMetaType;
    }
    
    struct NumericMetaType<I32> gIntMetaType;
    const MetaType &GetMetaType(I32) {
        return gIntMetaType;
    }
    
    struct NumericMetaType<U64> gULongIntMetaType;
    const MetaType &GetMetaType(U64) {
        return gULongIntMetaType;
    }
    
    struct NumericMetaType<I64> gLongIntMetaType;
    const MetaType &GetMetaType(I64) {
        return gLongIntMetaType;
    }
    
    //
    // float MetaType
    //
    struct NumericMetaType<F32> gFloatMetaType;
    const MetaType &GetMetaType(F32) {
        return gFloatMetaType;
    }
    
    //
    // Double Meta Type
    //
    struct NumericMetaType<F64> gDoubleMetaType;
    const MetaType &GetMetaType(double) {
        return gDoubleMetaType;
    }
    
    //
    // Void MetaType
    //
    struct VoidMetaType gVoidMetaType;
    
    const char* VoidMetaType::Name() const {
        return "void";
    }
    size_t VoidMetaType::SizeOf() const {
        return 0;
    }
    
    const void VoidMetaType::FromString(const std::string &str, void *outValue)const {
    }
    
    const std::string VoidMetaType::ToString(const void *v) const {
        return "";
    }
    
    const MetaType &GetMetaType(void) {
        return gVoidMetaType;
    }
    
    template<>
    const MetaType &GetMetaTypeByType<void>() {
        return GetMetaType();
    }
}