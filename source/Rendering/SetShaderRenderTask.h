#ifndef SETSHADERRENDERTASK_H_
#define SETSHADERRENDERTASK_H_

#include "RenderTask.h"
#include "../Geometry/Geometry.h"
#include "ShaderProgram.h"

namespace bde {

    /**
     * Render task that loads a geometry into Video Memory
     *
     * @author  Diego Jesus <diego.a.r.jz@gmail.com>
     * @date    28 May 2015
     */
    class SetShaderRenderTask : public RenderTask {
      private:
        ShaderProgramWeakPtr mShader;
      public:
        /* ****************************
         * Construction & Destruction *
         * ***************************/
        SetShaderRenderTask(ShaderProgramPtr shader);
        virtual ~SetShaderRenderTask();

        virtual void Execute(RendererPtr renderer) override;
    }; // class SetShaderRenderTask

} // namespace bde

#else
namespace bde {
    class SetShaderRenderTask;
} // namespace bde
#endif