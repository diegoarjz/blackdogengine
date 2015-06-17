#ifndef VERTEX_H_
#define VERTEX_H_

#include "../MathLib/MathUtils.h"

#include "VertexDescription.h"

namespace bde {

    /**
    * Default Vertex in the Black Dog Engine.
    *
    * A vertex is made of several semantic channels. A VertexDescription is
    * used to create VertexDataSources, one for each semantic channel.
    * Channels can be made of several components, e.g., a Vector3 channel has
    * 3 components.
    *
    * @author Diego Jesus <diego.a.r.jz@gmail.com>
    */
    class Vertex {
      public:
        static const VertexDescription description; ///< Describes the vertex semantics

        Vector3 mPosition;  ///< The vertex position
        Vector3 mNormal;    ///< The vertex normal
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
