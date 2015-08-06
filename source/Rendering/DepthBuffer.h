#ifndef DEPTH_BUFFER_H_
#define DEPTH_BUFFER_H_

#include "RenderState.h"
#include "../DataTypes.h"

namespace bde {
	
	/**
	* Indicates the state of the depth buffer for rendering.
	*/
    class DepthBuffer : public RenderState, public std::enable_shared_from_this<DepthBuffer>{
	public:
        enum DepthFunction{
            NEVER,
            LESS,
            EQUAL,
            LEQUAL,
            GREATER,
            NOTEQUAL,
            GEQUAL,
            ALWAYS,
        };
	private:
		BOOLEAN mEnabled;
		DepthFunction mFunction;	
    public:
        DepthBuffer();
		virtual ~DepthBuffer();
        
		BOOLEAN IsEnabled() const;
		void SetEnabled(const BOOLEAN &enabled);
		DepthFunction GetDepthFunction() const;
		void SetDepthFunction(const DepthFunction &function);

		virtual void Set(RenderingDevice* device) override;
        virtual RenderStateNames GetRenderStateName() override { return RenderState::DEPTH_BUFFER; }
    }; // class DepthBuffer
} // namespace bde

#else
namespace bde{
	class DepthBuffer;
} /* bde */
#endif