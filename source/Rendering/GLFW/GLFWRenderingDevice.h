#ifndef GLFWRENDERINGDEVICE_H_
#define GLFWRENDERINGDEVICE_H_

#ifdef __APPLE__

#include <OpenGL/GL.h>
#include <GLFW/glfw3.h>

#elif __linux

#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#endif

#include "../RenderingDevice.h"
#include "../Bindable.h"
#include "../../GameObject.h"

namespace bde {

    class GLFWRenderingDevice : public RenderingDevice, public std::enable_shared_from_this<GLFWRenderingDevice> {
      private:
        static const GLenum sShaderTypes[];
        static const GLenum sPrimitiveTypes[];
		static const GLenum sBlendFunctions[];
		static const GLenum sStencilFunctions[];
		static const GLenum sStencilOperations[];
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
        virtual void LoadGeometry(GeometryBasePtr geometry)override;
        virtual void BindVertexArray(BindingInfoPtr bi)override;
        virtual BindingInfoPtr  CreateVertexBuffer()override;
        virtual void BindVertexBuffer(BindingInfoPtr bi)override;
        virtual void LoadDataToVertexBuffer(BindingInfoPtr bi, GeometryBasePtr geometry) override;
        virtual void UnbindVertexBuffer(BindingInfoPtr bi)override;
        virtual void DeleteVertexBuffer(BindingInfoPtr bi)override;
        virtual void LoadElementBuffer(ElementDataSourcePtr elements)override;
        virtual void DrawElements(ElementDataSourcePtr elements)override;

        /* *********
         * Shaders *
         * ********/
        virtual void LoadShaderProgram(ShaderProgramPtr shaderProgram) override;
        virtual void LoadShader(ShaderPtr shader) override;
        virtual void SetShaderProgram(ShaderProgramPtr shaderProgram) override;

        /* *****************
         * Uniform Setting *
         * ****************/
        virtual void SetUniformValue(ShaderUniformPtr uniform, const float &f) override;
        virtual void SetUniformValue(ShaderUniformPtr uniform, const Vector2<> &v) override;
        virtual void SetUniformValue(ShaderUniformPtr uniform, const Vector3<> &v) override;
        virtual void SetUniformValue(ShaderUniformPtr uniform, const Vector4 &v) override;
        virtual void SetUniformValue(ShaderUniformPtr uniform, const Quaternion &q) override;
        virtual void SetUniformValue(ShaderUniformPtr uniform, const ColorRGB &c) override;
        virtual void SetUniformValue(ShaderUniformPtr uniform, const ColorRGBA &c) override;
        virtual void SetUniformValue(ShaderUniformPtr uniform, const Matrix3 &m) override;
        virtual void SetUniformValue(ShaderUniformPtr uniform, const Matrix4 &m) override;
        
        /* *******************
         * Shader Attributes *
         * ******************/
        virtual void SetAttributeValue(ShaderAttributePtr attribute, const float &f) override;
        virtual void SetAttributeValue(ShaderAttributePtr attribute, const Vector2<> &v) override;
        virtual void SetAttributeValue(ShaderAttributePtr attribute, const Vector3<> &v) override;
        virtual void SetAttributeValue(ShaderAttributePtr attribute, const Vector4 &v) override;
        virtual void SetAttributeValue(ShaderAttributePtr attribute, const Quaternion &q) override;
        virtual void SetAttributeValue(ShaderAttributePtr attribute, const ColorRGB &c) override;
        virtual void SetAttributeValue(ShaderAttributePtr attribute, const ColorRGBA &c) override;
        virtual void SetAttributeValue(ShaderAttributePtr attribute, const Matrix3 &m) override;
        virtual void SetAttributeValue(ShaderAttributePtr attribute, const Matrix4 &m) override;
		
		/* **********************
		* Render State Setting *
		* *********************/
		virtual void SetStencilState(std::shared_ptr<StencilState> stencil) override;
		virtual void SetAlphaBlend(std::shared_ptr<AlphaBlend> alpha) override;
		virtual void SetCullState(std::shared_ptr<CullState> cullState) override;
		virtual void SetDepthBuffer(std::shared_ptr<DepthBuffer> depth) override;
    private:
        void loadUniform(ShaderProgramPtr shader, std::shared_ptr<Bindable> uniform, const std::string &name);
		void setRenderStates(ShaderProgramPtr shader);
    }; // class GLFWRenderingDevice

    typedef std::shared_ptr<GLFWRenderingDevice> GLFWRenderingDevicePtr;
} // namespace bde

#else
namespace bde {
    class GLFWRenderingDevice;
} // namespace bde
#endif
