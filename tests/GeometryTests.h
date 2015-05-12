#ifndef GEOMETRYTESTS_H_
#define GEOMETRYTESTS_H_

#include <iostream>

#include <cpptest.h>

#include "../source/Geometry/Geometry.h"
#include "../source/Geometry/Vertex.h"
#include "../source/Geometry/ElementDataSource.h"
#include "../source/Geometry/VertexDataSource.h"
#include "../source/Geometry/VertexDataSourceSemantics.h"
#include "../source/Geometry/VertexDescription.h"

class GeometryTests : public Test::Suite{
public:
  GeometryTests(){
    TEST_ADD( GeometryTests::GeometryTest_CreateElementDataSource_CopiedArray );
    TEST_ADD( GeometryTests::GeometryTest_CreateGeometry_CorrectlyCopiedVerticesArray_VertexDataSources );
  }

protected:
  bde::U32 elements[6];
  bde::ElementDataSourcePtr elementsDS;
  bde::Vertex verts[4];
  std::map<bde::VertexDataSourceSemantics, bde::VertexDataSourcePtr> ds;
  bde::VertexDataSourcePtr posDS;
  bde::VertexDataSourcePtr norDS;

  virtual void setup(){
    bde::U32 els[] = {0,1,2, 0,2,3};
    bde::Vertex vs[] = {
      {bde::Vector3(0,0,0), bde::Vector3(0,0,1)},
      {bde::Vector3(1,0,0), bde::Vector3(0,0,1)},
      {bde::Vector3(1,1,0), bde::Vector3(0,0,1)},
      {bde::Vector3(0,1,0), bde::Vector3(0,0,1)},
    };

    memcpy(elements, els, sizeof(els));
    memcpy(verts, vs, sizeof(vs));

    elementsDS = std::make_shared<bde::ElementDataSource>(elements,bde::PrimitiveType::Triangles,2,6);
    posDS = std::make_shared<bde::VertexDataSource>(bde::VertexDataSourceSemantics::Position,4,true,3,sizeof(float),0,0);
    norDS = std::make_shared<bde::VertexDataSource>(bde::VertexDataSourceSemantics::Normal,4,true,3,sizeof(float),0,3*sizeof(float));

    ds[bde::VertexDataSourceSemantics::Position] = posDS;
    ds[bde::VertexDataSourceSemantics::Normal] = norDS;
  }
private:

  void GeometryTest_CreateElementDataSource_CopiedArray(){
    TEST_ASSERT( elementsDS->GetElements() != elements );

    for(int i=0; i<6; ++i){
      TEST_ASSERT( elements[i] == elementsDS->GetElements()[i] );
    }
  }

  void GeometryTest_CreateGeometry_CorrectlyCopiedVerticesArray_VertexDataSources(){
    bde::GeometryPtr geom = std::make_shared<bde::Geometry>(verts, 4, ds, elementsDS);

    // Test that the vertices have been correctly copied
    TEST_ASSERT( geom->GetVertices() != verts );
    for(int i=0; i<geom->GetVertexCount(); ++i){
      TEST_ASSERT( geom->GetVertices()[i] == verts[i] );
    }

    // Vertex Data Sources are correct
    auto vds = geom->GetVertexDataSourceForSemantics( bde::VertexDataSourceSemantics::Position );
    TEST_ASSERT( vds == posDS );
    TEST_ASSERT( vds->GetVertices() == geom->GetVertices() );
    auto nds = geom->GetVertexDataSourceForSemantics( bde::VertexDataSourceSemantics::Normal );
    TEST_ASSERT( nds == norDS );
    TEST_ASSERT( nds->GetVertices() == geom->GetVertices() );
  }
};

#endif
