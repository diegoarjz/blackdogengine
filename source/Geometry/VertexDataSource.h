#ifndef VERTEX_DATA_SOURCE_H_
#define VERTEX_DATA_SOURCE_H_

#include "../DataTypes.h"

#include "VertexDataSourceSemantics.h"
#include "Vertex.h"

namespace bde {

    /**
     * Indicates how an interleaved vertex data source should be read when
     * rendered.
     *
     * @author Diego Jesus <diego.a.r.jz@gmail.com>
     */
    class VertexDataSource {
      private:
        VertexDataSourceSemantics mSemantics;
        U32                       mVertexCount;
        BOOLEAN                   mIsFloat;
        U32                       mComponentCount;
        U32                       mBytesPerComponent;
        U32                       mOffset;
        U32                       mStride;
      public:

        /* ***************************
         * Construction & Destruction *
         * ***************************/
        VertexDataSource();
        VertexDataSource(const VertexDataSourceSemantics &semantics,
                         const U32 &vertexCount,
                         const BOOLEAN &isFloat,
                         const U32 &componentCount,
                         const U32 &bytesPerComponent,
                         const U32 &offset,
                         const U32 &stride);
        ~VertexDataSource();

        /* ******************
         * Getters & Setters *
         * ******************/
        VertexDataSourceSemantics   GetSemantics() const;
        U32                         GetVertexCount() const;
        BOOLEAN                     IsFloat() const;
        U32                         GetComponentCount() const;
        U32                         GetBytesPerComponent() const;
        U32                         GetOffset() const;
        U32                         GetStride() const;

        //  public: // static methods
        //
        //    static std::map<VertexDataSourceSemantics, std::shared_ptr<CustomVertexDataSource<vertex_t>>> CreateDataSources(std::vector<vertex_t> &vertices){
        //        std::map<VertexDataSourceSemantics, std::shared_ptr<CustomVertexDataSource<vertex_t>>> dataSources;
        //
        //        U64 vertexCount = vertices.size();
        //        U32 vertexSize = sizeof(vertex_t);
        //
        //        auto description = vertex_t::description;
        //        U32 offset = 0;
        //
        //        for(auto d : description){
        //            std::shared_ptr<CustomVertexDataSource<vertex_t>> ds = std::make_shared<CustomVertexDataSource<vertex_t>>( d.mSourceSemantics,
        //                    vertexCount,
        //                    d.mIsFloat,
        //                    d.mComponentCount,
        //                    d.mBytesPerComponent,
        //                    offset,
        //                    vertexSize);
        //
        //            offset += d.mComponentCount * d.mBytesPerComponent;
        //
        //            dataSources[ d.mSourceSemantics ] = ds;
        //        }
        //
        //        return dataSources;
        //    }
    }; // class VertexDataSource

    typedef std::shared_ptr<VertexDataSource> VertexDataSourcePtr;
    typedef std::weak_ptr<VertexDataSource> VertexDataSourceWeakPtr;
} // namespace bde

#endif
