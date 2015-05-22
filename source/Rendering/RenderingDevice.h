#ifndef RENDERING_DEVICE_H_
#define RENDERING_DEVICE_H_

#include "../DataTypes.h"
#include "../MathLib/ColorRGB.h"

namespace bde{

    /**
     * Interface for a rendering device.
     *
     * This creates a common interaface for higher levels of the rendering system
     * for specific platforms (e.g., OpenGL or DirectX).
     *
     * @author  Diego Jesus <diego.a.r.jz@gmail.com>
     * @date    18 May 2015
     */
    class RenderingDevice{
        private:

        public:
            /* ****************************
             * Construction & Destruction *
             * ***************************/
            RenderingDevice(){}
            virtual ~RenderingDevice(){}

            /* ******************
             * Context Creation *
             * *****************/
            virtual void CreateWindow(const U32 &width, const U32 &height, const U32 &poxX = 100, const U32 &posY = 100) = 0;
            virtual void CreateFullScreen() = 0;
            virtual bool ShouldClose() = 0;

            /* ********************
             * Background Methods *
             * *******************/
            virtual void SetBackgroundColor(const ColorRGB &bgColor) = 0;

            /* ****************
             * Buffer Methods *
             * ***************/
            virtual void ClearColorBuffer()     = 0;
            virtual void ClearDepthBuffer()     = 0;
            virtual void ClearStencilBuffer()   = 0;
            /**
             * Should clear all existing buffers.
             */
            virtual void ClearBuffers()         = 0;
            virtual void SwapBuffers()          = 0;
    }; // class RenderingDevice

    /// Smart pointer for a RenderingDevice
    typedef std::shared_ptr<RenderingDevice> RenderingDevicePtr;
} // namespace bde

#else
namespace bde{
    class RenderingDevice;
    typedef std::shared_ptr<RenderingDevice> RenderingDevicePtr;
} // namespace bde
#endif