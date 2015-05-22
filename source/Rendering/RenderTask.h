#ifndef RENDERTASK_H_
#define RENDERTASK_H_

#include "RenderingDevice.h"

namespace bde{
    class RenderTask{
        public:
            /* ****************************
             * Construction & Destruction *
             * ***************************/
            RenderTask();
            virtual ~RenderTask();

            virtual void Execute(RenderingDevicePtr device) = 0;
    }; // class RenderTask

    typedef std::shared_ptr<RenderTask> RenderTaskPtr;
} // namespace bde

#else
namespace bde{
    class RenderTask;
} // namespace bde
#endif
