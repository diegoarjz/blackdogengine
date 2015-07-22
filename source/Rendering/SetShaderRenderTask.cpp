#include "SetShaderRenderTask.h"

#include "../Debug/Logger.h"

namespace bde {
    /* ****************************
     * Construction & Destruction *
     * ***************************/
    SetShaderRenderTask::SetShaderRenderTask(ShaderProgramPtr shader) {
        mShader = shader;
    }

    SetShaderRenderTask::~SetShaderRenderTask() {
    }

    void SetShaderRenderTask::Execute(RendererPtr renderer) {
        //        LOG_INFO("Running Set Shader");
        renderer->GetRenderingDevice()->SetShaderProgram( mShader.lock() );
    }
}