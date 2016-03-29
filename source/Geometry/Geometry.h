#ifndef GEOMETRY_H_
#define GEOMETRY_H_

#include "../DataTypes.h"

#include "ElementDataSource.h"
#include "VertexDataSourceSemantics.h"
#include "VertexDataSource.h"
#include "../Rendering/BindingInfo.h"
#include "GeometryBase.h"

namespace bde {
    /**
     * Implements a templated GeometryBase class that is templated on
     * the type of vertex buffer.
     * This is a concrete class derived from the GeometryBase class.
     *
     * Each instance owns a vertex buffer of the type defined in the
     * template. This buffer is copied from the user specified buffer
     * in the constructor and is deleted during destruction.
     */
    template<typename V>
    class CustomGeometry : public GeometryBase {
      private:
        /// The vertex buffer.
        V *mVertices;
      public:
        /**
         * Constructs a CustomGeometry from the given vertex buffer
         * the vertex count, vertex data sources and element data
         * source.
         *
         * The constructor copies the vertex buffer, not taking
         * ownership of the original one. Therefore, the client
         * can delete the original buffer.
         */
        CustomGeometry(V *vertices,
                       const U32 &vertexCount,
                       const std::map<VertexDataSourceSemantics, VertexDataSourcePtr> &dataSources,
                       ElementDataSourcePtr elements) : GeometryBase(vertexCount, dataSources,
                                   elements) {
            mVertices = new Vertex[vertexCount * sizeof(V)];
            memcpy(mVertices, vertices, vertexCount * sizeof(V));
        }

        virtual ~CustomGeometry() {
            delete [] mVertices;
        }

        /**
         * Returns the pointer to the vertex buffer
         */
        const V *GetVertices() const {
            return mVertices;
        }

        /**
         * Returns a void pointer to the vertex buffer.
         */ 
        virtual const void *GetVertexBuffer() const override {
            return (void *)mVertices;
        }
    }; // class Geometry

    /// Type for a shared, smart pointer to a CustomGeometry.
    template<typename vertex_t>
    using CustomGeometryPtr = std::shared_ptr<CustomGeometry<vertex_t>>;

    /** The default geometry in Black Dog Engine is a CustomGeometry with
     * the default Vertex.
     */
    typedef CustomGeometry<Vertex>          Geometry;
    /// Type for a shared, smart pointer to the default geometry.
    typedef std::shared_ptr<Geometry>       GeometryPtr;
    /// Type for a weak pointer to the default geometry.
    typedef std::weak_ptr<Geometry>         GeometryWeakPtr;
} // namespace bde

#else

namespace bde {

} // namespace bde

#endif
