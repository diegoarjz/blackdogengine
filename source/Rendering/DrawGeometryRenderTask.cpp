#include "DrawGeometryRenderTask.h"

#include "../Debug/Logger.h"

namespace bde {
    /* ****************************
     * Construction & Destruction *
     * ***************************/
    DrawGeometryRenderTask::DrawGeometryRenderTask(GeometryPtr geometry) {
        mGeometry = geometry;
    }

    DrawGeometryRenderTask::~DrawGeometryRenderTask() {
    }

    void DrawGeometryRenderTask::Execute(RenderingDevicePtr device) {
        device->BindVertexArray( mGeometry.lock()->GetVertexArrayBindingInfo() );
        device->DrawElements( mGeometry.lock()->GetElementDataSource() );
    }
} // namespace bde