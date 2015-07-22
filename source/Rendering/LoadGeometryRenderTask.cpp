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

    void LoadGeometryRenderTask::Execute(RendererPtr renderer) {
        //        LOG_INFO( "Running LoadGeometryTask ");
        
        renderer->GetRenderingDevice()->LoadGeometry( mGeometry.lock() );
    }
} // namespace bde
