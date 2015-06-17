#include "VertexDataSource.h"


namespace bde {

    /* ***************************
     * Construction & Destruction *
     * ***************************/
    VertexDataSource::VertexDataSource() {
        mSemantics         = VertexDataSourceSemantics::NULL_SEMANTICS;
        mVertexCount       = 0;
        mIsFloat           = false;
        mComponentCount    = 0;
        mBytesPerComponent = 0;
        mOffset            = 0;
        mStride            = 0;
    }

    VertexDataSource::VertexDataSource(const VertexDataSourceSemantics &semantics,
                                       const U32 &vertexCount,
                                       const BOOLEAN &isFloat,
                                       const U32 &componentCount,
                                       const U32 &bytesPerComponent,
                                       const U32 &offset,
                                       const U32 &stride) {
        mSemantics         = semantics;
        mVertexCount       = vertexCount;
        mIsFloat           = isFloat;
        mComponentCount    = componentCount;
        mBytesPerComponent = bytesPerComponent;
        mOffset            = offset;
        mStride            = stride;
    }

    VertexDataSource::~VertexDataSource() {
    }

    /* ******************
     * Getters & Setters *
     * ******************/
    VertexDataSourceSemantics VertexDataSource::GetSemantics() const {
        return mSemantics;
    }

    U32 VertexDataSource::GetVertexCount() const {
        return mVertexCount;
    }

    BOOLEAN VertexDataSource::IsFloat() const {
        return mIsFloat;
    }

    U32 VertexDataSource::GetComponentCount() const {
        return mComponentCount;
    }

    U32 VertexDataSource::GetBytesPerComponent() const {
        return mBytesPerComponent;
    }

    U32 VertexDataSource::GetOffset() const {
        return mOffset;
    }

    U32 VertexDataSource::GetStride() const {
        return mStride;
    }

} // namespace bde