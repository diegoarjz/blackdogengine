#ifndef VERTEX_DESCRIPTION_H_
#define VERTEX_DESCRIPTION_H_

#include <vector>

#include "../DataTypes.h"

#include "VertexDataSourceSemantics.h"

namespace bde{

  /**
  * Describes the semantic of a vertex semantic channel.
  *
  * @author Diego Jesus <diego.a.r.jz@gmail.com>
  */
  struct VertexChannelDescription{
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
