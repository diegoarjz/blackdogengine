#include "Renderer.h"

#include "../Debug/Logger.h"

namespace bde {


    /* ****************************
     * Construction & Destruction *
     * ***************************/
    Renderer::Renderer() {
        mRenderPool = std::make_shared<RenderPool>();
    }

    /* *******************
     * Getters & Setters *
     * ******************/
    RenderingDevicePtr  Renderer::GetRenderingDevice() const {
        return mRenderingDevice;
    }

    void                Renderer::SetRenderingDevice(RenderingDevicePtr device) {
        mRenderingDevice = device;
    }

    RenderPoolPtr       Renderer::GetRenderPool() const {
        return mRenderPool;
    }

    void                Renderer::SetRenderPool(RenderPoolPtr renderPool) {
        mRenderPool = renderPool;
    }
    
    CameraPtr Renderer::GetCurrentCamera() const{
        return mCurrentCamera;
    }
    
    void Renderer::SetCurrentCamera(CameraPtr cam){
        mCurrentCamera = cam;
    }

    void Renderer::Start() {
        // check that we have a rendering device
        if( mRenderingDevice == nullptr) {
            throw std::runtime_error("Couldn't start the renderer: No rendering device set.");
        }

        // and a rendering pool
        if( mRenderPool == nullptr) {
            throw std::runtime_error("Couldn't start the renderer: No RenderPool set.");
        }

        // notify that the renderer is ready
        mRenderPool->NotifyRenderReady();
        // and wait for the update cycle to be ready
        mRenderPool->WaitForUpdateReady();
        // create a window (for now)
#warning TODO: this should not be hardcoded
        mRenderingDevice->CreateWindow(500, 500);

        // While the rendering device indicates that it should stay
        // open, meaning that the user hasn't closed the window
        // we execute all render tasks
        while( !mRenderingDevice->ShouldClose() ) {
            // Start by clearing the buffers
            mRenderingDevice->ClearBuffers();
            // Read the render pool
            auto pool = mRenderPool->GetCurrentFrameQueue();

            while(!pool.empty()) {
                auto task = pool.front();
                pool.pop();
                task->Execute( shared_from_this() );
            }

            mRenderingDevice->SwapBuffers();
            mRenderPool->NotifyRenderDone();
            mRenderPool->WaitForSwapDone();
        }
    }
} // namespace  bde
