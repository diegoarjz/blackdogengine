//
//  GeometryBase.h
//  BlackDogEngine
//
//  Created by Diego Jesus on 02/06/15.
//
//

#ifndef __BlackDogEngine__GeometryBase__
#define __BlackDogEngine__GeometryBase__

#include "../DataTypes.h"

#include "ElementDataSource.h"
#include "VertexDataSourceSemantics.h"
#include "VertexDataSource.h"
#include "../Rendering/BindingInfo.h"

namespace bde {
    class GeometryBase {
      protected:
        U32                     mVertexCount;
        VertexDataSourcePtr
        mVertexDataSources[VertexDataSourceSemantics::MAX_VERTEX_DATA_SOURCE_SEMANTICS];
        ElementDataSourcePtr    mElementDataSource;
        BindingInfoPtr          mBindingInfo;
        BindingInfoPtr          mVertexArrayBindingInfo;
      public:
        /* ****************************
         * Construction & Destruction *
         * ***************************/
        GeometryBase(const U32 &vertexCount,
                     const std::map<VertexDataSourceSemantics, VertexDataSourcePtr> &dataSources,
                     ElementDataSourcePtr elements);
        virtual ~GeometryBase();

        /* *******************
         * Getters & Setters *
         * ******************/
        U32                     GetVertexCount() const;
        VertexDataSourcePtr     GetVertexDataSourceForSemantics(
            const VertexDataSourceSemantics &s);
        ElementDataSourcePtr    GetElementDataSource();
        BindingInfoPtr          GetBindingInfo();
        void                    SetBindingInfo(BindingInfoPtr bi);
        BindingInfoPtr          GetVertexArrayBindingInfo();
        void                    SetVertexArrayBindingInfo(BindingInfoPtr bi);

        virtual const void *GetVertexBuffer() const = 0;
    }; // class CustomGeometryBase

    typedef std::shared_ptr<GeometryBase> GeometryBasePtr;
} // namespace bde

#else
namespace bde {
    class GeometryBase;
    typedef std::shared_ptr<GeometryBase> GeometryBasePtr;
} // namespace bde
#endif /* defined(__BlackDogEngine__GeometryBase__) */
