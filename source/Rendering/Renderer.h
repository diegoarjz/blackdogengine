#ifndef RENDERER_H_
#define RENDERER_H_

#include "RenderingDevice.h"
#include "RenderPool.h"

#include "../DataTypes.h"
#include "../Camera.h"

namespace bde {

    /**
     * Interface for the Rendering system.
     *
     * The update thread submits render tasks to the RenderPool
     * which, in turn, are fetched by the renderer at the correct
     * time.
     *
     * This class also holds a pointer to the currently active camera,
     * which is used by render tasks to set the corresponding matrices.
     */
    class Renderer : public std::enable_shared_from_this<Renderer>{
      private:
        /// The rendering device to where rendering calls are made
        RenderingDevicePtr mRenderingDevice;
        /// The render pool from where tasks are fetched
        RenderPoolPtr mRenderPool;
        /// The currently active camera
        CameraPtr mCurrentCamera;
      public:
        Renderer();

        RenderingDevicePtr  GetRenderingDevice() const;
        void                SetRenderingDevice(RenderingDevicePtr device);
        RenderPoolPtr       GetRenderPool() const;
        void                SetRenderPool(RenderPoolPtr renderPool);
        CameraPtr GetCurrentCamera() const;
        void SetCurrentCamera(CameraPtr cam);

        /**
         * Starts the rendering.
         *
         * This checks if there is a RenderingDevice and a RenderPool
         * attached. Throws an exception otherwise.
         *
         * Starts by notifying the RenderPool that the Renderer is
         * ready and awaits for the update thread to be ready.
         *
         * Once this happens, the Renderer asks the rendering device to create
         * a window. The Renderer then enters a loop that will only end when
         * the window is closed (by checking the RenderingDevice::ShouldClose()).
         *
         * During this loop, the rendering buffers are cleared, the next framed is
         * fetched from the RenderPool and all RenderTasks are dequed from that queue
         * and are executed in turn. Finally, the Renderer requests the Rendering device
         * to swap the buffers, notifies the RenderPool that the rendering is complete 
         * and waits for the RenderPool to swap the frames.
         */
        void Start();
    }; // class Renderer

    typedef std::shared_ptr<Renderer> RendererPtr;
} // namespace bde

#else

namespace bde {
    class Renderer;
    typedef std::shared_ptr<Renderer> RendererPtr;
}

#endif
