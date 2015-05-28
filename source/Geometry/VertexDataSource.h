#ifndef VERTEX_DATA_SOURCE_H_
#define VERTEX_DATA_SOURCE_H_

#include "../DataTypes.h"

#include "VertexDataSourceSemantics.h"
#include "Vertex.h"

namespace bde {

  /**
  * Indicates how an interleaved vertex data source should be read when
  * rendered.
  *
  * @author Diego Jesus <diego.a.r.jz@gmail.com>
  */
  template<typename vertex_t>
  class CustomVertexDataSource{
  private:
    vertex_t                  *mVertices;
    VertexDataSourceSemantics mSemantics;
    U32                       mVertexCount;
    BOOLEAN                   mIsFloat;
    U32                       mComponentCount;
    U32                       mBytesPerComponent;
    U32                       mOffset;
    U32                       mStride;
  public:

    /* ***************************
    * Construction & Destruction *
    * ***************************/
    CustomVertexDataSource(){
      mVertices          = NULL;
      mSemantics         = VertexDataSourceSemantics::NULL_SEMANTICS;
      mVertexCount       = 0;
      mIsFloat           = false;
      mComponentCount    = 0;
      mBytesPerComponent = 0;
      mOffset            = 0;
      mStride            = 0;
    }

    CustomVertexDataSource(const VertexDataSourceSemantics &semantics,
                           const U32 &vertexCount,
                           const BOOLEAN &isFloat,
                           const U32 &componentCount,
                           const U32 &bytesPerComponent,
                           const U32 &offset,
                           const U32 &stride){

      mVertices          = NULL;
      mSemantics         = semantics;
      mVertexCount       = vertexCount;
      mIsFloat           = isFloat;
      mComponentCount    = componentCount;
      mBytesPerComponent = bytesPerComponent;
      mOffset            = offset;
      mStride            = stride;

    }

    ~CustomVertexDataSource(){

    }

    /* ******************
    * Getters & Setters *
    * ******************/
    const vertex_t* GetVertices() const{
      return mVertices;
    }

    void SetVertices(vertex_t* vertices){
      mVertices = vertices;
    }

    VertexDataSourceSemantics GetSemantics() const{
      return mSemantics;
    }

    U32 GetVertexCount() const{
      return mVertexCount;
    }

    BOOLEAN IsFloat() const{
      return mIsFloat;
    }

    U32 GetComponentCount() const{
      return mComponentCount;
    }

    U32 GetBytesPerComponent() const{
      return mBytesPerComponent;
    }

    U32 GetOffset() const{
      return mOffset;
    }

    U32 GetStride() const{
      return mStride;
    }

  public: // static methods

    static std::map<VertexDataSourceSemantics, std::shared_ptr<CustomVertexDataSource<vertex_t>>> CreateDataSources(std::vector<vertex_t> &vertices){
        std::map<VertexDataSourceSemantics, std::shared_ptr<CustomVertexDataSource<vertex_t>>> dataSources;
    
        U64 vertexCount = vertices.size();
        U32 vertexSize = sizeof(vertex_t);
        vertex_t *vert_ptr = &(vertices[0]);

        auto description = vertex_t::description;
        U32 offset = 0;

        for(auto d : description){
            std::shared_ptr<CustomVertexDataSource<vertex_t>> ds = std::make_shared<CustomVertexDataSource<vertex_t>>( d.mSourceSemantics,
                    vertexCount,
                    d.mIsFloat,
                    d.mComponentCount,
                    d.mBytesPerComponent,
                    offset,
                    vertexSize);

            offset += d.mComponentCount * d.mBytesPerComponent;

            dataSources[ d.mSourceSemantics ] = ds;
        }

        return dataSources;
    }
  }; // class VertexDataSource

  template<typename vertex_t>
  using CustomVertexDataSourcePtr = std::shared_ptr<CustomVertexDataSource<vertex_t>>;

  typedef CustomVertexDataSource<Vertex> VertexDataSource;
  typedef std::shared_ptr<VertexDataSource> VertexDataSourcePtr;
} // namespace bde

#endif
