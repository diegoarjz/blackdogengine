#ifndef RENDERSTATE_H_
#define RENDERSTATE_H_

#include <memory>

namespace bde{

	class RenderingDevice;
	
	/** 
	* Base class for all render states.
	*/
	class RenderState{
	public:
		enum RenderStateNames{
			ALPHA_BLEND,
			DEPTH_BUFFER,
			CULL,
			STENCIL_STATE,
            
			MAX_RENDER_STATES
		};
	protected:
		/* *************
		* Constructor *
		* ************/
		RenderState();
	public:
		/* ************
		* Destructor *
		* ***********/
		virtual ~RenderState();
        
		virtual void Set(RenderingDevice* device) = 0;
		virtual RenderStateNames GetRenderStateName() = 0;
	}; // class RenderState

	typedef std::shared_ptr<RenderState> RenderStatePtr;
} // namespace bde

#else
namespace bde{
	class RenderState;
	typedef std::shared_ptr<RenderState> RenderStatePtr;
} /* bde */
#endif