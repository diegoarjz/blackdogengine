#ifndef __BlackDogEngine__GeometryBase__
#define __BlackDogEngine__GeometryBase__

#include <map>

#include "../DataTypes.h"

#include "ElementDataSource.h"
#include "VertexDataSourceSemantics.h"
#include "VertexDataSource.h"
#include "../Rendering/BindingInfo.h"

namespace bde {
    /**
     * Base class for a geometry.
     * A geometry is composed of several vertex data sources
     * each with different semantics and an element data source.
     *
     * Vertex data sources are used to describe how a given 
     * semantic vertex channel is read from the vertex buffer.
     * The element data source describes which type of primitives
     * are represented and how they are constructed from the vertex
     * buffer.
     * 
     * The GeometryBase is an abstract class that does not 
     * hold vertex data information. Instead concrete derived
     * classes are expected to hold a pointer to
     * a buffer holding vertex data.
     *
     * This way, different types of vertices can be used, while
     * the vertex data sources and element data source are used 
     * to explain how a geometry is constructed from the vertex
     * buffer.
     *
     */
    class GeometryBase {
        public:
            constexpr static int max_vertex_channels = VertexDataSourceSemantics::MAX_VERTEX_DATA_SOURCE_SEMANTICS;
      protected:
        /// Number of vertices in the geometry.
        U32 mVertexCount;
        /// The semantic vertex data sources.
        VertexDataSourcePtr mVertexDataSources[max_vertex_channels];
        /// The element data source, describing how primitives are created.
        ElementDataSourcePtr mElementDataSource;
        
        BindingInfoPtr mBindingInfo;
        BindingInfoPtr mVertexArrayBindingInfo;
      public:
        /**
         * Creates a geometry given a count of vertices, a map
         * of vertex semantics to vertex data sources and an 
         * element data source.
         *
         * If the map does not contain a vertex data source for a 
         * given semantics, then that channel is set to nullptr.
         */
        GeometryBase(const U32 &vertexCount,
                     const std::map<VertexDataSourceSemantics, VertexDataSourcePtr> &dataSources,
                     ElementDataSourcePtr elements);
        virtual ~GeometryBase();

        /**
         * Returns the number of vertices in the geometry.
         */
        U32 GetVertexCount() const;
        /**
         * Returns the semantic data source for the given semantics.
         */
        VertexDataSourcePtr GetVertexDataSourceForSemantics(const VertexDataSourceSemantics &s);
        /**
         * Returns the element data source.
         */
        ElementDataSourcePtr GetElementDataSource();
        
        BindingInfoPtr GetBindingInfo();
        void SetBindingInfo(BindingInfoPtr bi);
        BindingInfoPtr GetVertexArrayBindingInfo();
        void SetVertexArrayBindingInfo(BindingInfoPtr bi);

        /**
         * Returns a pointer to the vertex buffer.
         * 
         * Derived, concrete classes must implement this method.
         */
        virtual const void *GetVertexBuffer() const = 0;
    }; // class CustomGeometryBase

    /// Shared smart pointer for a GeometryBase.
    using GeometryBasePtr = std::shared_ptr<GeometryBase>;
} // namespace bde

#else
namespace bde {
    class GeometryBase;
    using GeometryBasePtr = std::shared_ptr<GeometryBase>;
} // namespace bde
#endif /* defined(__BlackDogEngine__GeometryBase__) */
