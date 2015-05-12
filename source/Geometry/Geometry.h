#ifndef GEOMETRY_H_
#define GEOMETRY_H_

#include "../DataTypes.h"

#include "ElementDataSource.h"
#include "VertexDataSourceSemantics.h"
#include "VertexDataSource.h"

namespace bde{

  /**
  * Implements geometry information that can be rendered.
  *
  * @author Diego Jesus <diego.a.r.jz@gmail.com>
  */
  template<typename V, typename I>
  class CustomGeometry{
  private:
    V                             *mVertices;
    U32                           mVertexCount;
    CustomVertexDataSourcePtr<V>  mVertexDataSources[VertexDataSourceSemantics::MAX_VERTEX_DATA_SOURCE_SEMANTICS];
    CustomElementDataSourcePtr<I> mElementDataSource;
  public:

    /* ***************************
    * Construction & Destruction *
    * ***************************/
    CustomGeometry(V *vertices,
             const U32 &vertexCount,
             const std::map<VertexDataSourceSemantics, CustomVertexDataSourcePtr<V>> &dataSources,
             CustomElementDataSourcePtr<I> elements){

      mVertices = new Vertex[vertexCount * sizeof(V)];
      memcpy(mVertices, vertices, vertexCount * sizeof(V));
      mVertexCount = vertexCount;

      for(auto ds : dataSources){
        mVertexDataSources[(int)ds.first] = ds.second;
        ds.second->SetVertices(mVertices);
      }

      mElementDataSource = elements;
    }

    ~CustomGeometry(){
      delete [] mVertices;
    }

    /* ******************
    * Getters & Setters *
    * ******************/
    const V* GetVertices() const{
      return mVertices;
    }

    U32 GetVertexCount() const{
      return mVertexCount;
    }

    CustomVertexDataSourcePtr<V> GetVertexDataSourceForSemantics(const VertexDataSourceSemantics &s){
      return mVertexDataSources[s];
    }

  }; // class Geometry

  template<typename vertex_t, typename I>
  using CustomGeometryPtr = std::shared_ptr<CustomGeometry<vertex_t, I>>;

  typedef CustomGeometry<Vertex, U32> Geometry;
  typedef std::shared_ptr<Geometry> GeometryPtr;
} // namespace bde

#else

namespace bde{

} // namespace bde

#endif
