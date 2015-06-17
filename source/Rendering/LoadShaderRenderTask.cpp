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

    void LoadShaderRenderTask::Execute(RenderingDevicePtr device) {
        //        LOG_INFO( "Running LoadShader ");
        device->LoadShaderProgram( mShader.lock() );
    }

} // namespace bde