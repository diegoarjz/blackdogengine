#ifndef DRAWGEOMETRYRENDERTASK_H_
#define DRAWGEOMETRYRENDERTASK_H_

#include "RenderTask.h"
#include "../Geometry/Geometry.h"

namespace bde {

    /**
     * Render task that loads a geometry into Video Memory
     *
     * @author  Diego Jesus <diego.a.r.jz@gmail.com>
     * @date    28 May 2015
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
