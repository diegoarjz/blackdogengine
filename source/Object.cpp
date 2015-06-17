#include "Object.h"
#include <iostream>
#include <sstream>
#include <iomanip>

namespace bde {
    /* ***************************
     * Run Time Type Information *
     * **************************/
    const Rtti Object::TYPE("bde.Object", nullptr);
    uid_t Object::sNextUID=0;

    bool Object::IsType (const Rtti &rkType) const {
        return GetType().IsType(rkType);
    }

    bool Object::IsInstanceOf (const Rtti &rkType) const {
        return GetType().IsInstanceOf(rkType);
    }

    bool Object::IsType (const Object *pkObj) const {
        return pkObj && GetType().IsType(pkObj->GetType());
    }

    bool Object::IsInstanceOf (const Object *pkObj) const {
        return pkObj && GetType().IsInstanceOf(pkObj->GetType());
    }

    /* **************
     * Constructors *
     * *************/
    Object::Object() {
        mUID = sNextUID++;
    }

    /* ********************
     * Reference Counting *
     * *******************/
    /* ***********************
     * Object Identification *
     * **********************/
    void Object::SetName(const std::string &name) {
        mName = name;
    }

    const std::string &Object::GetName() const {
        return mName;
    }

    uid_t Object::GetUID() const {
        return mUID;
    }

    std::string Object::ToString() const {
        std::stringstream res;
        res << GetType().GetName() << "[0x" << std::setfill('0') << std::setw(
                8) << std::hex <<  mUID << "] \"" << mName << "\"";
        return res.str();
    }

    ObjectPtr Object::Search(const std::string &name) {
        if(mName == name) {
            return shared_from_this();
        }

        return nullptr;
    }

    ObjectPtr Object::Search(uid_t UID) {
        if(mUID == UID) {
            return shared_from_this();
        }

        return nullptr;
    }

    std::string Object::StringTree(U16 indentation) {
        std::stringstream res;

        for(int i=0; i<indentation; i++) {
            res << "-";
        }

        res << " " << ToString();
        return res.str();
    }

    std::ostream &operator<< (std::ostream &stream, const Object &o) {
        stream << o.GetType().GetName() << "[0x" << std::setfill('0') << std::setw(
                   8) << std::hex << o.mUID << "] \"" << o.mName << "\"";
        return stream;
    }

    /* ************
     * Destructor *
     * ***********/
    Object::~Object() {
    }
}
