#include "GeometryBase.h"

#include <cassert>
#include <iostream>

namespace bde {
    /* ****************************
     * Construction & Destruction *
     * ***************************/
    GeometryBase::GeometryBase(const U32 &vertexCount,
                               const std::map<VertexDataSourceSemantics, VertexDataSourcePtr> &dataSources,
                               ElementDataSourcePtr elements) {
        mVertexCount = vertexCount;

        // Set every position in the vertex data source array to nullptr
        memset(mVertexDataSources, 0, sizeof(VertexDataSourcePtr)*max_vertex_channels);
        // For each of the vertex data sources in the map,
        // set its corresponding position in the vertex
        // data source array
        for(auto ds : dataSources) {
            mVertexDataSources[static_cast<int>(ds.first)] = ds.second;
        }

        mElementDataSource = elements;
    }

    GeometryBase::~GeometryBase() {
    }

    /* *******************
     * Getters & Setters *
     * ******************/
    U32 GeometryBase::GetVertexCount() const {
        return mVertexCount;
    }

    VertexDataSourcePtr GeometryBase::GetVertexDataSourceForSemantics(
        const VertexDataSourceSemantics &s) {
        return mVertexDataSources[s];
    }

    ElementDataSourcePtr GeometryBase::GetElementDataSource() {
        return mElementDataSource;
    }

    BindingInfoPtr GeometryBase::GetBindingInfo() {
        return mBindingInfo;
    }

    void GeometryBase::SetBindingInfo(BindingInfoPtr bi) {
        // Can only set the binding info if there isn't one already set.
        assert(mBindingInfo == nullptr);
        mBindingInfo = bi;
    }

    BindingInfoPtr      GeometryBase::GetVertexArrayBindingInfo() {
        return mVertexArrayBindingInfo;
    }

    void                GeometryBase::SetVertexArrayBindingInfo(BindingInfoPtr bi) {
        mVertexArrayBindingInfo = bi;
    }

} // namespace bde
