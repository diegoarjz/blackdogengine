#ifndef RENDERPOOL_H_
#define RENDERPOOL_H_

#include <queue>

#include "../DataTypes.h"
#include "RenderTask.h"
#include "../System/Mutex.h"
#include "../System/AutoResetEvent.h"
#include "../Debug/Logger.h"

namespace bde {
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
        RenderPool() {
            mCurrentFrame = 0;
        }

        ~RenderPool() {
        }

        void Push(RenderTaskPtr task) {
            mFrames[NextFrame()].push(task);
        }

        void NotifyUpdateReady(){
            //LOG_INFO("Notifying update ready");
            mUpdateReadyEvent.Notify();
        }

        void WaitForUpdateReady(){
            //LOG_INFO("Waiting For Update ready");
            mUpdateReadyEvent.Wait();
        }

        void WaitForRenderReady(){
            //LOG_INFO("Wait for render ready");
            mRenderReadyEvent.Wait();
        }

        void NotifyRenderReady(){
            //LOG_INFO("Notifying render ready");
            mRenderReadyEvent.Notify();
        }

        void NotifyRenderDone(){
            //LOG_INFO("Notifying render done");
            mRenderDoneEvent.Notify();
        }

        void WaitForRenderDone(){
            //LOG_INFO("Waiting for render done");
            mRenderDoneEvent.Wait();
        }

        void SwapRenderQueues(){
            //LOG_INFO("Swapping render queues");
            mFrames[mCurrentFrame] = std::queue<RenderTaskPtr>();
            mCurrentFrame = (mCurrentFrame + 1) % 2;
        }

        void NotifySwapDone(){
            //LOG_INFO("Notifying swap done");
            mSwapDoneEvent.Notify();
        }

        void WaitForSwapDone(){
            //LOG_INFO("Waiting for swap done");
            mSwapDoneEvent.Wait();
        }

        U32 CurrentFrame() {
            return mCurrentFrame;
        }

        U32 NextFrame() {
            return (CurrentFrame() + 1) % 2;
        }

        std::queue<RenderTaskPtr> GetCurrentFrameQueue() {
            return mFrames[CurrentFrame()];
        }
    }; // class CustomRenderPool

    typedef std::shared_ptr<RenderPool> RenderPoolPtr;      ///< Type definition for a pointer to a RenderPool.
} // namespace bde

#else
namespace bde {
    class RenderPool;
} // namespace bde
#endif
