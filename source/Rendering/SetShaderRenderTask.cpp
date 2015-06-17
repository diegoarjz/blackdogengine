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

    void SetShaderRenderTask::Execute(RenderingDevicePtr device) {
        //        LOG_INFO("Running Set Shader");
        device->SetShaderProgram( mShader.lock() );
    }
}