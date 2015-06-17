#include "SetBackgroundColorRenderTask.h"

#include "../Debug/Logger.h"

namespace bde {
    /* ****************************
     * Construction & Destruction *
     * ***************************/
    SetBackgroundColorRenderTask::SetBackgroundColorRenderTask(
        const ColorRGB &backgroundColor) {
        mBackgroundColor = backgroundColor;
    }

    SetBackgroundColorRenderTask::~SetBackgroundColorRenderTask() {
    }

    void SetBackgroundColorRenderTask::Execute(RenderingDevicePtr device) {
        //        LOG_INFO( "Running SetBackgroundColo ");
        device->SetBackgroundColor(mBackgroundColor);
    }
} // namespace bde
