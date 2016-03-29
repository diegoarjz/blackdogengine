#ifndef VERTEX_DATA_SOURCE_H_
#define VERTEX_DATA_SOURCE_H_

#include "../DataTypes.h"

#include "VertexDataSourceSemantics.h"
#include "Vertex.h"

namespace bde {

    /**
     * Indicates how a specific semantic channel of vertex data
     * (e.g., position or normals) should be read from a  vertex buffer.
     */
    class VertexDataSource {
      private:
        /// The data source semantics.
        VertexDataSourceSemantics mSemantics;
        /// The number of vertices
        U32 mVertexCount;
        /// Indicates if the data source elements are floats.
        BOOLEAN mIsFloat;
        /// The number of components per vertex.
        U32 mComponentCount;
        /// The number of bytes per component
        U32 mBytesPerComponent;
        /// The offset within a vertex buffer
        U32 mOffset;
        /// The stride between elements in a vertex buffer.
        U32 mStride;
      public:
        /**
         * Constructs a vertex data source with a null semantics.
         */
        VertexDataSource();
        /**
         * Constructs the vertex data source with the given
         * semantics and parameters.
         */
        VertexDataSource(
                /// The semantics for the data source
                const VertexDataSourceSemantics &semantics,
                /// The number of vertices.
                const U32 &vertexCount,
                /// If the data is float.
                const BOOLEAN &isFloat,
                /// Number of components in each vertex.
                const U32 &componentCount,
                /// Number of bytes in each component.
                const U32 &bytesPerComponent,
                /// The offset within a vertex buffer
                const U32 &offset,
                /// The stride between elements in a vertex buffer
                const U32 &stride);

        /**
         * Returns the semantics of this data source.
         */
        VertexDataSourceSemantics GetSemantics() const;
        /**
         * Returns the number of vertices.
         */
        U32 GetVertexCount() const;
        /**
         * Returns wether the data in this data source
         * is float or not.
         */
        BOOLEAN IsFloat() const;
        /**
         * Returns the number of components per vertex.
         */
        U32 GetComponentCount() const;
        /**
         * Returns the number of bytes per vertex
         * component.
         */
        U32 GetBytesPerComponent() const;
        /**
         * Returns the offset in the data source.
         */
        U32 GetOffset() const;
        /**
         * Returns the stride in the vertex buffer.
         */
        U32 GetStride() const;
    }; // class VertexDataSource

    typedef std::shared_ptr<VertexDataSource> VertexDataSourcePtr;
    typedef std::weak_ptr<VertexDataSource> VertexDataSourceWeakPtr;
} // namespace bde

#endif
