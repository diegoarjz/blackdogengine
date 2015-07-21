#ifndef RENDERPOOL_H_
#define RENDERPOOL_H_

#include <queue>

#include "../DataTypes.h"
#include "RenderTask.h"
#include "../System/Mutex.h"
#include "../System/AutoResetEvent.h"
#include "../Debug/Logger.h"

namespace bde {
    /**
     * The update thread queues render tasks in one frame, while
     * the render thread dequeues them from another frame.
     *
     * Has some methods that allows the proper synchronisation between threads.
     * Upon intialization, the update thread sends the UpdateReady event and waits for the
     * RenderReady event. Similarily, the render thread sends the ReaderReady event and waits for
     * the UpdateReady event. This way, neither the update thread starts pushing render
     * tasks ahead of time, nor the render thread begins reading tasks before.
     *
     * Each frame, the update thread submits render tasks to the next frame (n+1). When 
     * finished, it waits for the RenderDone event. In the mean time, the render thread is
     * busy performing the render tasks from the current frame (n) and, when complete, it sends the
     * RenderDone event, and waits for the SwapDone event.
     *
     * The RenderDone event is received by the update thread which, afterwards triggers the
     * buffer swap and sends the SwapDone event.
     *
     * This mechanism allows the proper synchronisation between threads and allows the
     * creation of the next frame to execute while the current is being rendered.
     */
    class RenderPool {
      private:
        std::queue<RenderTaskPtr>   mFrames[2];
        U32                         mCurrentFrame;
        AutoResetEvent              mRenderReadyEvent;
        AutoResetEvent              mRenderDoneEvent;
        AutoResetEvent              mUpdateReadyEvent;
        AutoResetEvent              mSwapDoneEvent;
      public:
        /* ****************************
         * Construction & Destruction *
         * ***************************/
        RenderPool();
        ~RenderPool();

        /*
         * Notifications
         */
        void NotifyUpdateReady();
        void WaitForUpdateReady();

        void NotifyRenderReady();
        void WaitForRenderReady();

        void NotifyRenderDone();
        void WaitForRenderDone();

        void NotifySwapDone();
        void WaitForSwapDone();

        void Push(RenderTaskPtr task);
        void SwapRenderQueues();
        U32 CurrentFrame();
        U32 NextFrame();
        std::queue<RenderTaskPtr> GetCurrentFrameQueue();
    }; // class CustomRenderPool

    typedef std::shared_ptr<RenderPool>
    RenderPoolPtr;      ///< Type definition for a pointer to a RenderPool.
} // namespace bde

#else
namespace bde {
    class RenderPool;
} // namespace bde
#endif
