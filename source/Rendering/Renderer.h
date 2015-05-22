#ifndef RENDERER_H_
#define RENDERER_H_

#include "RenderingDevice.h"
#include "RenderPool.h"

#include "../DataTypes.h"

namespace bde{

    /**
     * Interface for the Rendering system.
     *
     * @author  Diego Jesus <diego.a.r.jz@gmail.com>
     * @date    18 May 2015
     */
    class Renderer{
        private:
            RenderingDevicePtr  mRenderingDevice;
            RenderPoolPtr       mRenderPool;
        public:
            /* ****************************
             * Construction & Destruction *
             * ***************************/
            Renderer();
            ~Renderer();

            /* *******************
             * Getters & Setters *
             * ******************/
            RenderingDevicePtr  GetRenderingDevice() const;
            void                SetRenderingDevice(RenderingDevicePtr device);
            RenderPoolPtr       GetRenderPool() const;
            void                SetRenderPool(RenderPoolPtr renderPool);


            void Start();
    }; // class Renderer

    typedef std::shared_ptr<Renderer> RendererPtr;
} // namespace bde

#else

namespace bde{
    class Renderer;
}

#endif
