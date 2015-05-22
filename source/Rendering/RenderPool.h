#ifndef RENDERPOOL_H_
#define RENDERPOOL_H_

#include <queue>

#include "../DataTypes.h"
#include "RenderTask.h"
#include "../System/Mutex.h"

namespace bde{
    template<int numFrames>
    class CustomRenderPool{
        private:
            std::queue<RenderTaskPtr>   mFrames[numFrames];
            U32                         mCurrentFrame;
            Mutex                       mCurrentFrameMutex;
        public:
            /* ****************************
             * Construction & Destruction *
             * ***************************/
            CustomRenderPool(){
                mCurrentFrame = 0;
            }

            ~CustomRenderPool(){
            }

            void Push(RenderTaskPtr task){
                mFrames[NextFrame()].push(task);
            }

            void FinishFrame(){
                mCurrentFrameMutex.Lock();
                mCurrentFrame = (mCurrentFrame + 1) % numFrames; 
                mCurrentFrameMutex.Unlock();
            }

            U32 CurrentFrame(){
                return mCurrentFrame;
            }

            U32 NextFrame(){
                return (CurrentFrame() + 1) % numFrames;
            }

            std::queue<RenderTaskPtr> GetCurrentFrameQueue(){
                mCurrentFrameMutex.Lock();
                auto currentQueue = mFrames[CurrentFrame()];
                mFrames[CurrentFrame()] = std::queue<RenderTaskPtr>();
                mCurrentFrameMutex.Unlock();

                return currentQueue;
            }
    }; // class CustomRenderPool

    typedef CustomRenderPool<2> RenderPool;                 ///< RenderPool with two frames
    typedef std::shared_ptr<RenderPool> RenderPoolPtr;      ///< Type definition for a pointer to a RenderPool with 2 frames
} // namespace bde

#else
namespace bde{
    class RenderPool;
} // namespace bde
#endif
