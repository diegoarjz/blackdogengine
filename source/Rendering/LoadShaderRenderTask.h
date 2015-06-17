#ifndef LOADSHADERRENDERTASK_H_
#define LOADSHADERRENDERTASK_H_

#include "RenderTask.h"
#include "ShaderProgram.h"

namespace bde {

    /**
     * Render task that loads a geometry into Video Memory
     *
     * @author  Diego Jesus <diego.a.r.jz@gmail.com>
     * @date    28 May 2015
     */
    class LoadShaderRenderTask : public RenderTask {
      private:
        ShaderProgramWeakPtr mShader;
      public:
        /* ****************************
         * Construction & Destruction *
         * ***************************/
        LoadShaderRenderTask(ShaderProgramPtr shader);
        virtual ~LoadShaderRenderTask();

        virtual void Execute(RenderingDevicePtr device);

    }; // class LoadShaderRenderTask

} // namespace bde

#else
namespace bde {
    class LoadShaderRenderTask;
} // namespace bde
#endif