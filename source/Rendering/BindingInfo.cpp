#include "BindingInfo.h"

#include <cassert>

namespace bde {

    BindingInfo::BindingInfo(const U32 &id) {
        mBindingID = id;
        mBound = false;
    }

    BindingInfo::~BindingInfo() {
        // should crash if the binding info is destroyed without being released
        assert( !mBound );
    }

    /* *******************
     * Getters & Setters *
     * ******************/
    U32 BindingInfo::GetBindingID() const {
        return mBindingID;
    }

    bool BindingInfo::IsBound() const {
        return mBound;
    }

    void BindingInfo::Bind() {
        mBound = true;
    }

    void BindingInfo::Unbind() {
        mBound = false;
    }

    std::ostream &operator<< (std::ostream &stream, const BindingInfo &o) {
        stream << "BindingInfo[" << o.mBindingID << "]";
        return stream;
    }
} // namespace bde
