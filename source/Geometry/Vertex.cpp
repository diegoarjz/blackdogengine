#include "Vertex.h"

#include "VertexDataSourceSemantics.h"

namespace bde {

    const VertexDescription Vertex::description = {
        //                           Semantics, float, #comps,        bytes
        { VertexDataSourceSemantics::Position ,  true,      3,sizeof(float) },  // Position
        { VertexDataSourceSemantics::Normal   ,  true,      3,sizeof(float) }   // Normal
    };

    bool operator==(const Vertex &v1, const Vertex &v2) {
        return (v1.mPosition == v2.mPosition) && (v1.mNormal == v2.mNormal);
    }

    bool operator!=(const Vertex &v1, const Vertex &v2) {
        return !(v1==v2);
    }

    std::ostream &operator<<(std::ostream &o, const Vertex &v) {
        o << "Position: " << v.mPosition << " Normal: " << v.mNormal << std::endl;
        return o;
    }

} // namespace bde
