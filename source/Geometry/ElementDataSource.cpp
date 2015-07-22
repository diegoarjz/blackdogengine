#include "ElementDataSource.h"

#include <cstring>

namespace bde {
    ElementDataSource::ElementDataSource(const U32 *elements,
                                         const PrimitiveType &primitiveType,
                                         const U32 &primitiveCount,
                                         const U32 &elementCount) {
        mElements = new U32[ elementCount * sizeof(U32) ];
        memcpy(mElements, elements, elementCount * sizeof(U32) );
        mPrimitiveType  = primitiveType;
        mPrimitiveCount = primitiveCount;
        mElementsCount  = elementCount;
    }

    ElementDataSource::~ElementDataSource() {
        delete []mElements;
    }

    /* ******************
     * Getters & Setters *
     * ******************/
    const U32 *ElementDataSource::GetElements() const {
        return mElements;
    }

    PrimitiveType ElementDataSource::GetPrimitiveType() const {
        return mPrimitiveType;
    }

    U32 ElementDataSource::GetPrimitiveCount() const {
        return mPrimitiveCount;
    }

    U32 ElementDataSource::GetElementsCount() const {
        return mElementsCount;
    }

    U32 ElementDataSource::GetSizeInBytes()const {
        return mElementsCount*sizeof(U32);
    }

    BindingInfoPtr ElementDataSource::GetBindingInfo() {
        return mBindingInfo;
    }

    void ElementDataSource::SetBindingInfo(BindingInfoPtr bi) {
        mBindingInfo = bi;
    }
} // namespace bde
