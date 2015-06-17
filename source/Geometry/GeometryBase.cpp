#include "GeometryBase.h"

namespace bde {
    /* ****************************
     * Construction & Destruction *
     * ***************************/
    GeometryBase::GeometryBase(const U32 &vertexCount,
                               const std::map<VertexDataSourceSemantics, VertexDataSourcePtr> &dataSources,
                               ElementDataSourcePtr elements) {
        mVertexCount = vertexCount;

        for(auto ds : dataSources) {
            mVertexDataSources[(int)ds.first] = ds.second;
        }

        mElementDataSource = elements;
    }

    GeometryBase::~GeometryBase() {
        std::cout << "Destroying geometry" << std::endl;
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