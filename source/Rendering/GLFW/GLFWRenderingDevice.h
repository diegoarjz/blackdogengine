#ifndef GLFWRENDERINGDEVICE_H_
#define GLFWRENDERINGDEVICE_H_

#include <GLFW/glfw3.h>
#include "../RenderingDevice.h"

namespace bde {

    class GLFWRenderingDevice : public RenderingDevice {
      private:
        static const GLenum sShaderTypes[];
        static const GLenum sPrimitiveTypes[];
      private:
        GLFWwindow *mWindow;
      public:
        /* ****************************
         * Construction & Destruction *
         * ***************************/
        GLFWRenderingDevice();
        virtual ~GLFWRenderingDevice();

        /* ******************
         * Context Creation *
         * *****************/
        virtual void CreateWindow(const U32 &width, const U32 &height,
                                  const U32 &poxX = 100, const U32 &posY = 100) override;
        virtual void CreateFullScreen() override;
        virtual bool ShouldClose() override;

        /* ********************
         * Background Methods *
         * *******************/
        virtual void SetBackgroundColor(const ColorRGB &bgColor) override;

        /* ****************
         * Buffer Methods *
         * ***************/
        virtual void ClearColorBuffer() override;
        virtual void ClearDepthBuffer() override;
        virtual void ClearStencilBuffer() override;
        /**
         * Should clear all existing buffers.
         */
        virtual void ClearBuffers() override;
        virtual void SwapBuffers() override;

        /* ******************
         * Geometry Loading *
         * *****************/
        virtual void            LoadGeometry(GeometryBasePtr geometry)
        override;
        virtual void            BindVertexArray(BindingInfoPtr bi)
        override;
        virtual BindingInfoPtr  CreateVertexBuffer()
        override;
        virtual void            BindVertexBuffer(BindingInfoPtr bi)
        override;
        virtual void            LoadDataToVertexBuffer(BindingInfoPtr bi,
                GeometryBasePtr geometry) override;
        virtual void            UnbindVertexBuffer(BindingInfoPtr bi)
        override;
        virtual void            DeleteVertexBuffer(BindingInfoPtr bi)
        override;
        virtual void            LoadElementBuffer(ElementDataSourcePtr elements)
        override;
        virtual void            DrawElements(ElementDataSourcePtr elements)
        override;

        /* *********
         * Shaders *
         * ********/
        virtual void    LoadShaderProgram(ShaderProgramPtr shaderProgram) override;
        virtual void    LoadShader(ShaderPtr shader) override;
        virtual void    SetShaderProgram(ShaderProgramPtr shaderProgram) override;
        virtual void    UnloadShader(ShaderPtr shader) override;

    }; // class GLFWRenderingDevice

    typedef std::shared_ptr<GLFWRenderingDevice> GLFWRenderingDevicePtr;
} // namespace bde

#else
namespace bde {
    class GLFWRenderingDevice;
} // namespace bde
#endif
