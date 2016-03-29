#ifndef VERTEX_H_
#define VERTEX_H_

#include "VertexDescription.h"
#include "../MathLib/Vector3.h"

namespace bde {

    /**
    * Default Vertex in the Black Dog Engine.
    *
    * A vertex is made of several semantic channels.
    *
    * The  VertexDescription describes the elements of this vertex, its semantics,
    * number of components, size per component and wether each component is a
    * floating point value.
    * It can be used to create VertexDataSources, one for each semantic channel.
    * Channels can be made of several components, e.g., a Vector3 channel has
    * 3 components.
    */
    class Vertex {
      public:
        static const VertexDescription description; ///< Describes the vertex semantics

        Vector3f mPosition;  ///< The vertex position
        Vector3f mNormal;    ///< The vertex normal
    };

    bool operator==(const Vertex &v1, const Vertex &v2);
    bool operator!=(const Vertex &v1, const Vertex &v2);
    std::ostream &operator<<(std::ostream &o, const Vertex &v);

} // namespace bde

#else
namespace bde {
    class Vertex;
} // namespace bde
#endif
