#ifndef LOADGEOMETRYRENDERTASK_H_
#define LOADGEOMETRYRENDERTASK_H_

#include "RenderTask.h"
#include "../Geometry/Geometry.h"

namespace bde {

    /**
     * Render task that loads a geometry into Video Memory
     *
     * @author  Diego Jesus <diego.a.r.jz@gmail.com>
     * @date    28 May 2015
     */
    class LoadGeometryRenderTask : public RenderTask {
      private:
        GeometryWeakPtr mGeometry;
      public:
        /* ****************************
         * Construction & Destruction *
         * ***************************/
        LoadGeometryRenderTask(GeometryPtr mGeometry);
        virtual ~LoadGeometryRenderTask();

        virtual void Execute(RendererPtr renderer) override;

    }; // class LoadGeometryRenderTask

} // namespace bde

#else
namespace bde {
    class LoadGeometryRenderTask;
} // namespace bde
#endif
