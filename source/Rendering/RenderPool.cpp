#include "RenderPool.h"

namespace bde {

    /* ****************************
     * Construction & Destruction *
     * ***************************/
    RenderPool::RenderPool() {
        mCurrentFrame = 0;
    }

    RenderPool::~RenderPool() {
    }

    void RenderPool::Push(RenderTaskPtr task) {
        mFrames[NextFrame()].push(task);
    }

    void RenderPool::SwapRenderQueues() {
        mFrames[mCurrentFrame] = std::queue<RenderTaskPtr>();
        mCurrentFrame = (mCurrentFrame + 1) % 2;
    }

    /*
     * Notifications
     */
    void RenderPool::NotifyUpdateReady() {
        mUpdateReadyEvent.Notify();
    }

    void RenderPool::WaitForUpdateReady() {
        mUpdateReadyEvent.Wait();
    }

    void RenderPool::WaitForRenderReady() {
        mRenderReadyEvent.Wait();
    }

    void RenderPool::NotifyRenderReady() {
        mRenderReadyEvent.Notify();
    }

    void RenderPool::NotifyRenderDone() {
        mRenderDoneEvent.Notify();
    }

    void RenderPool::WaitForRenderDone() {
        mRenderDoneEvent.Wait();
    }

    void RenderPool::NotifySwapDone() {
        mSwapDoneEvent.Notify();
    }

    void RenderPool::WaitForSwapDone() {
        mSwapDoneEvent.Wait();
    }

    U32 RenderPool::CurrentFrame() {
        return mCurrentFrame;
    }

    U32 RenderPool::NextFrame() {
        return (CurrentFrame() + 1) % 2;
    }

    std::queue<RenderTaskPtr> RenderPool::GetCurrentFrameQueue() {
        return mFrames[CurrentFrame()];
    }

} // namespace bde