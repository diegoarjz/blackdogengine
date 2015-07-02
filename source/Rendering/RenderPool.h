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
