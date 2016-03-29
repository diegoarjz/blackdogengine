#ifndef BlackDogEngine_create_vertex_data_sources_h
#define BlackDogEngine_create_vertex_data_sources_h

#include "VertexDataSource.h"
#include "VertexDataSourceSemantics.h"

namespace bde {

    template<class vertex_t>
    std::map<VertexDataSourceSemantics, std::shared_ptr<VertexDataSource>>
    create_vertex_data_sources(std::vector<vertex_t> &vertices) {
        std::map<VertexDataSourceSemantics, std::shared_ptr<VertexDataSource>>
                dataSources;
        U64 vertexCount = vertices.size();
        U32 vertexSize = sizeof(vertex_t);
        auto description = vertex_t::description;
        U32 offset = 0;

        for(auto d : description) {
            std::shared_ptr<VertexDataSource> ds = std::make_shared<VertexDataSource>
                                                   (d.mSourceSemantics,
                                                    vertexCount,
                                                    d.mIsFloat,
                                                    d.mComponentCount,
                                                    d.mBytesPerComponent,
                                                    offset,
                                                    vertexSize);
            offset += d.mComponentCount * d.mBytesPerComponent;
            dataSources[ d.mSourceSemantics ] = ds;
        }

        return dataSources;
    }

} // namespace bde

#endif
