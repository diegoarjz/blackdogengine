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
     * Implements geometry information that can be rendered.
     *
     * @author Diego Jesus <diego.a.r.jz@gmail.com>
     * @date   1 May 2015
     */
    template<typename V>
    class CustomGeometry : public GeometryBase {
      private:
        V                             *mVertices;
      public:

        /* ***************************
         * Construction & Destruction *
         * ***************************/
        CustomGeometry(V *vertices,
                       const U32 &vertexCount,
                       const std::map<VertexDataSourceSemantics, VertexDataSourcePtr> &dataSources,
                       ElementDataSourcePtr elements) : GeometryBase(vertexCount, dataSources,
                                   elements) {
            mVertices = new Vertex[vertexCount * sizeof(V)];
            memcpy(mVertices, vertices, vertexCount * sizeof(V));
        }

        ~CustomGeometry() {
            delete [] mVertices;
        }

        /* ******************
         * Getters & Setters *
         * ******************/
        const V *GetVertices() const {
            return mVertices;
        }

        virtual const void       *GetVertexBuffer() const override {
            return (void *)mVertices;
        }
    }; // class Geometry

    template<typename vertex_t>
    using CustomGeometryPtr = std::shared_ptr<CustomGeometry<vertex_t>>;

    typedef CustomGeometry<Vertex>          Geometry;
    typedef std::shared_ptr<Geometry>       GeometryPtr;
    typedef std::weak_ptr<Geometry>         GeometryWeakPtr;
} // namespace bde

#else

namespace bde {

} // namespace bde

#endif
