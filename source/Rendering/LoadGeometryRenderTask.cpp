#include "LoadGeometryRenderTask.h"

#include "../Debug/Logger.h"

namespace bde {
    /* ****************************
     * Construction & Destruction *
     * ***************************/
    LoadGeometryRenderTask::LoadGeometryRenderTask(GeometryPtr geometry) {
        mGeometry = geometry;
    }

    LoadGeometryRenderTask::~LoadGeometryRenderTask() {
    }

    void LoadGeometryRenderTask::Execute(RenderingDevicePtr device) {
        //        LOG_INFO( "Running LoadGeometryTask ");
        device->LoadGeometry( mGeometry.lock() );
    }
} // namespace bde
