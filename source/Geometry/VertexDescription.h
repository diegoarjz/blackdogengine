#ifndef VERTEX_DESCRIPTION_H_
#define VERTEX_DESCRIPTION_H_

#include <vector>

#include "../DataTypes.h"

#include "VertexDataSourceSemantics.h"

namespace bde {

    /**
    * Describes a vertex channel in a vertex buffer.
    *
    * It indicates the semantics of a channel, wether the 
    * channel has floating point components, the number of comonents
    * for each vertex and the size in bytes per component.
    */
    struct VertexChannelDescription {
        /// The semantics of a vertex channel.
        VertexDataSourceSemantics mSourceSemantics;
        /// Indicates if the channel components are floating point values.
        BOOLEAN                   mIsFloat;
        /// Number of components per channel item.
        U32                       mComponentCount;
        /// Number of bytes of each components.
        U32                       mBytesPerComponent;
    };

    /**
    * Describes all channels in a vertex.
    */
    typedef std::vector<VertexChannelDescription> VertexDescription;

} // namespace bde

#else

#endif
