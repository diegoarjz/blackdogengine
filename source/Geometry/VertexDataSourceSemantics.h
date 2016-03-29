#ifndef VERTEX_DATA_SOURCE_SEMANTICS_H_
#define VERTEX_DATA_SOURCE_SEMANTICS_H_

namespace bde {
    /**
    * Describes the semantics of a channel in a vertex buffer.
    * It can be used in the rendering to pass data to the shaders.
    */
    enum VertexDataSourceSemantics {
        Position = 0,
        Normal,
        MAX_VERTEX_DATA_SOURCE_SEMANTICS,
        NULL_SEMANTICS
    };

} // namespace bde

#endif
