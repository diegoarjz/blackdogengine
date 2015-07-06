#ifndef SETMATERIALRENDERTASK_H_
#define SETMATERIALRENDERTASK_H_

#include "RenderTask.h"
#include "Material.h"

namespace bde {
    
    /**
     * Render task that sets a material.
     *
     */
    class SetMaterialRenderTask : public RenderTask {
    private:
        MaterialPtr mMaterial;
    public:
        /* ****************************
         * Construction & Destruction *
         * ***************************/
        SetMaterialRenderTask(MaterialPtr material);
        virtual ~SetMaterialRenderTask();
        
        virtual void Execute(RenderingDevicePtr device);
    }; // class SetMaterialRenderTask
    
} // namespace bde

#else
namespace bde {
    class SetMaterialRenderTask;
} // namespace bde
#endif