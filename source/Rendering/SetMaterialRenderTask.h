#ifndef SETMATERIALRENDERTASK_H_
#define SETMATERIALRENDERTASK_H_

#include "RenderTask.h"
#include "Material.h"
#include "../GameObject.h"

namespace bde {
    
    /**
     * Render task that sets a material.
     *
     */
    class SetMaterialRenderTask : public RenderTask {
    private:
        MaterialPtr mMaterial;
        GameObjectPtr mGameObject;
    public:
        /* ****************************
         * Construction & Destruction *
         * ***************************/
        SetMaterialRenderTask(MaterialPtr material, GameObjectPtr gameObject);
        virtual ~SetMaterialRenderTask();
        
        virtual void Execute(RendererPtr renderer) override;
    }; // class SetMaterialRenderTask
    
} // namespace bde

#else
namespace bde {
    class SetMaterialRenderTask;
} // namespace bde
#endif