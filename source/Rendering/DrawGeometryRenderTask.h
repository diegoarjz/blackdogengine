#ifndef DRAWGEOMETRYRENDERTASK_H_
#define DRAWGEOMETRYRENDERTASK_H_

#include "RenderTask.h"
#include "../Geometry/Geometry.h"

namespace bde {

    /**
     * Render task that loads a geometry into Video Memory
     */
    class DrawGeometryRenderTask : public RenderTask {
      private:
        GeometryWeakPtr mGeometry;
      public:
        /* ****************************
         * Construction & Destruction *
         * ***************************/
        DrawGeometryRenderTask(GeometryPtr mGeometry);
        virtual ~DrawGeometryRenderTask();

        virtual void Execute(RendererPtr renderer) override;

    }; // class DrawGeometryRenderTask

} // namespace bde

#else
namespace bde {
    class DrawGeometryRenderTask;
} // namespace bde
#endif
