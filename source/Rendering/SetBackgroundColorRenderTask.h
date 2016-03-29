#ifndef SETBACKGROUNDCOLORRENDERTASK_H_
#define SETBACKGROUNDCOLORRENDERTASK_H_

#include "RenderTask.h"
#include "../MathLib/ColorRGB.h"

namespace bde {
    /**
     *
     */
    class SetBackgroundColorRenderTask : public RenderTask {
      private:
        ColorRGB    mBackgroundColor;
      public:
        /* ****************************
         * Construction & Destruction *
         * ***************************/
        SetBackgroundColorRenderTask(const ColorRGB &backgroundColor);
        virtual ~SetBackgroundColorRenderTask();

        virtual void Execute(RendererPtr renderer) override;

    }; // class SetBackgroundColorRenderTask
} // namespace bde

#else
namespace bde {
    class SetBackgroundColorRenderTask;
} // namespace bde
#endif
