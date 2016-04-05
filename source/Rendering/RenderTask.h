#ifndef RENDERTASK_H_
#define RENDERTASK_H_

#include "Renderer.h"

namespace bde {
    /**
     * Performs a given task on the Rendering Device.
     * Objects of this type are queued in a RenderPool and are fetched
     * by the Renderer thread and executed in sequence, creating a frame.
     */
    class RenderTask {
      public:
        /* ****************************
         * Construction & Destruction *
         * ***************************/
        RenderTask();
        virtual ~RenderTask();

        /**
         * Abstract method to execute the rendering task.
         *
         * Subclasses must provide their implementation.
         */
        virtual void Execute(RendererPtr renderer) = 0;
    }; // class RenderTask

    /// Smart, shared pointer to a RenderTask.
    using RenderTaskPtr = std::shared_ptr<RenderTask>;
} // namespace bde

#else
namespace bde {
    class RenderTask;
    using RenderTaskPtr = std::shared_ptr<RenderTask>;
} // namespace bde
#endif
