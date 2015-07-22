#ifndef RENDERING_DEVICE_H_
#define RENDERING_DEVICE_H_

#include "../DataTypes.h"
#include "../MathLib/ColorRGB.h"
#include "../Geometry/Geometry.h"
#include "../GameObject.h"
#include "Shader.h"
#include "BindingInfo.h"
#include "ShaderAttribute.h"

namespace bde {

    class ShaderProgram;
    typedef std::shared_ptr<ShaderProgram> ShaderProgramPtr;
    
    class Material;
    typedef std::shared_ptr<Material> MaterialPtr;
    
    class ShaderUniformBase;
    typedef std::shared_ptr<ShaderUniformBase> ShaderUniformPtr;
    
    /**
     * Interface for a rendering device.
     *
     * This creates a common interaface for higher levels of the rendering system
     * for specific platforms (e.g., OpenGL or DirectX).
     *
     * @author  Diego Jesus <diego.a.r.jz@gmail.com>
     * @date    18 May 2015
     */
    class RenderingDevice {
      private:

      public:
        /* ****************************
         * Construction & Destruction *
         * ***************************/
        RenderingDevice() {}
        virtual ~RenderingDevice() {}

        /* ******************
         * Context Creation *
         * *****************/
        virtual void CreateWindow(const U32 &width, 
                                  const U32 &height,
                                  const U32 &poxX = 100,
                                  const U32 &posY = 100) = 0;
        virtual void CreateFullScreen() = 0;
        virtual bool ShouldClose() = 0;

        /* ********************
         * Background Methods *
         * *******************/
        virtual void SetBackgroundColor(const ColorRGB &bgColor) = 0;

        /* ****************
         * Buffer Methods *
         * ***************/
        virtual void ClearColorBuffer() = 0;
        virtual void ClearDepthBuffer() = 0;
        virtual void ClearStencilBuffer() = 0;
        /**
         * Should clear all existing buffers.
         */
        virtual void ClearBuffers() = 0;
        virtual void SwapBuffers() = 0;

        /* ******************
         * Geometry Loading *
         * *****************/
        virtual void LoadGeometry(GeometryBasePtr geometry) = 0;
        virtual BindingInfoPtr CreateVertexBuffer() = 0;
        virtual void BindVertexBuffer(BindingInfoPtr bi) = 0;
        virtual void LoadDataToVertexBuffer(BindingInfoPtr bi, GeometryBasePtr geometry) = 0;
        virtual void UnbindVertexBuffer(BindingInfoPtr bi) = 0;
        virtual void DeleteVertexBuffer(BindingInfoPtr bi) = 0;
        virtual void LoadElementBuffer(ElementDataSourcePtr elements) = 0;
        virtual void BindVertexArray(BindingInfoPtr bi) = 0;
        
        /* *********
         * Drawing *
         * ********/
        virtual void DrawElements(ElementDataSourcePtr elements) = 0;

        /* ****************
         * Shader Loading *
         * ***************/
        virtual void LoadShaderProgram(ShaderProgramPtr shaderProgram) = 0;
        virtual void LoadShader(ShaderPtr shader) = 0;
        virtual void SetShaderProgram(ShaderProgramPtr shaderProgram) = 0;

        /* *****************
         * Uniform Setting *
         * ****************/
        virtual void SetUniformValue(ShaderUniformPtr uniform, const float &f) = 0;
        virtual void SetUniformValue(ShaderUniformPtr uniform, const Vector2 &v) = 0;
        virtual void SetUniformValue(ShaderUniformPtr uniform, const Vector3 &v) = 0;
        virtual void SetUniformValue(ShaderUniformPtr uniform, const Vector4 &v) = 0;
        virtual void SetUniformValue(ShaderUniformPtr uniform, const Quaternion &q) = 0;
        virtual void SetUniformValue(ShaderUniformPtr uniform, const ColorRGB &c) = 0;
        virtual void SetUniformValue(ShaderUniformPtr uniform, const ColorRGBA &c) = 0;
        virtual void SetUniformValue(ShaderUniformPtr uniform, const Matrix3 &m) = 0;
        virtual void SetUniformValue(ShaderUniformPtr uniform, const Matrix4 &m) = 0;
        
        virtual void SetAttributeValue(ShaderAttributePtr attribute, const float &f) = 0;
        virtual void SetAttributeValue(ShaderAttributePtr attribute, const Vector2 &v) = 0;
        virtual void SetAttributeValue(ShaderAttributePtr attribute, const Vector3 &v) = 0;
        virtual void SetAttributeValue(ShaderAttributePtr attribute, const Vector4 &v) = 0;
        virtual void SetAttributeValue(ShaderAttributePtr attribute, const Quaternion &q) = 0;
        virtual void SetAttributeValue(ShaderAttributePtr attribute, const ColorRGB &c) = 0;
        virtual void SetAttributeValue(ShaderAttributePtr attribute, const ColorRGBA &c) = 0;
        virtual void SetAttributeValue(ShaderAttributePtr attribute, const Matrix3 &m) = 0;
        virtual void SetAttributeValue(ShaderAttributePtr attribute, const Matrix4 &m) = 0;
        
    }; // class RenderingDevice

    /// Smart pointer for a RenderingDevice
    typedef std::shared_ptr<RenderingDevice> RenderingDevicePtr;
} // namespace bde

#else
namespace bde {
    class RenderingDevice;
    typedef std::shared_ptr<RenderingDevice> RenderingDevicePtr;
} // namespace bde
#endif
