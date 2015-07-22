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

    void SetBackgroundColorRenderTask::Execute(RendererPtr renderer) {
        renderer->GetRenderingDevice()->SetBackgroundColor(mBackgroundColor);
    }
} // namespace bde
