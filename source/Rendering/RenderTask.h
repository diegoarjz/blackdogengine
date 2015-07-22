#ifndef RENDERTASK_H_
#define RENDERTASK_H_

#include "Renderer.h"

namespace bde {
    
    /**
     * Performs a given task on the Rendering Device.
     * Objects of this type are queued in a RenderPool and are fetched
     * by the Renderer thread and executed in sequence, creating a frame.
     *
     * @author  Diego Jesus <diego.a.r.jz@gmail.com>
     * @date    18 May 2015
     */
    class RenderTask {
      public:
        /* ****************************
         * Construction & Destruction *
         * ***************************/
        RenderTask();
        virtual ~RenderTask();

        virtual void Execute(RendererPtr renderer) = 0;
    }; // class RenderTask

    typedef std::shared_ptr<RenderTask> RenderTaskPtr;
} // namespace bde

#else
namespace bde {
    class RenderTask;
    typedef std::shared_ptr<RenderTask> RenderTaskPtr;
} // namespace bde
#endif
