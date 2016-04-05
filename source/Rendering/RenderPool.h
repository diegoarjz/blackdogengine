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
     *
     * The current frame queue is the one that is currently being rendered.
     */
    class RenderPool {
      public:
        using pool_t = std::queue<RenderTaskPtr>;
      private:
        /// The frame queues.
        pool_t mFrames[2];
        /// Index for the currently being rendered.
        U32 mCurrentFrame;
        /// Event for the render ready notification.
        AutoResetEvent mRenderReadyEvent;
        /// Event for the render done notification.
        AutoResetEvent mRenderDoneEvent;
        /// Event for the update ready notification.
        AutoResetEvent mUpdateReadyEvent;
        /// Event for the frame swap done notification.
        AutoResetEvent mSwapDoneEvent;
      public:
        RenderPool();
        
        /**
         * Notifies the RenderPool that the update thread
         * is ready.
         *
         * This is called by the update thread on initialisation.
         */
        void NotifyUpdateReady();
        /**
         * Waits for until the update thread is ready.
         *
         * This is called by the Renderer on initialisation.
         */
        void WaitForUpdateReady();

        /**
         * Notifies the RenderPool that the Renderer is ready.
         *
         * This is called by the Renderer on initialisation.
         */
        void NotifyRenderReady();
        /**
         * Waits until the Renderer is ready.
         *
         * This is called by the update thread on initialisation.
         */
        void WaitForRenderReady();
        /**
         * Notifies that the Renderer has completed rendering
         * the current frame.
         *
         * Called by the Renderer during execution, once finished
         * executing all RenderTask.
         */
        void NotifyRenderDone();
        /**
         * Waits until the Renderer has finished rendering.
         *
         * Called by the update thread during execution, after queueing
         * all RenderTask for the next frame.
         */
        void WaitForRenderDone();

        /**
         * Notifies that the render queues have been swapped.
         * 
         * Called by the update thread during execution, after swapping
         * the render queues.
         */
        void NotifySwapDone();
        /**
         * Waits until the render queues have been swapped.
         *
         * Called by the Renderer during execution, after finishing
         * all RenderTask.
         */
        void WaitForSwapDone();

        /**
         * Inserts a RenderTask into the queue for the next frame.
         */
        void Push(RenderTaskPtr task);
        /**
         * Indicates that the update thread has completed the next frame.
         *
         * This triggers the swap of the render queues.
         */
        void SwapRenderQueues();
        /**
         * Returns the render queue that should be rendered.
         */
        pool_t GetCurrentFrameQueue();
    private:
        U32 CurrentFrame();
        U32 NextFrame();
    }; // class CustomRenderPool

    using RenderPoolPtr = std::shared_ptr<RenderPool>; ///< Type definition for a pointer to a RenderPool.
} // namespace bde

#else
namespace bde {
    class RenderPool;
    using RenderPoolPtr = std::shared_ptr<RenderPool>;
} // namespace bde
#endif
