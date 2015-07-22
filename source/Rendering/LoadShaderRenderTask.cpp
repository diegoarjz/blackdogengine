#include "LoadShaderRenderTask.h"

#include "../Debug/Logger.h"

namespace bde {
    /* ****************************
     * Construction & Destruction *
     * ***************************/
    LoadShaderRenderTask::LoadShaderRenderTask(ShaderProgramPtr shader) {
        mShader = shader;
    }

    LoadShaderRenderTask::~LoadShaderRenderTask() {
    }

    void LoadShaderRenderTask::Execute(RendererPtr renderer) {
        //        LOG_INFO( "Running LoadShader ");
        renderer->GetRenderingDevice()->LoadShaderProgram( mShader.lock() );
    }

} // namespace bde