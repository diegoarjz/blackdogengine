#ifndef ALPHA_BLEND_H_
#define ALPHA_BLEND_H_

#include "../DataTypes.h"

#include "RenderState.h"

namespace bde{
	class AlphaBlend : public RenderState, public std::enable_shared_from_this<AlphaBlend>{
	public:
		enum BlendFunction{
			ZERO, 
			ONE, 
			SRC_COLOR,
			ONE_MINUS_SRC_COLOR, 
			DST_COLOR,
			ONE_MINUS_DST_COLOR,
			SRC_ALPHA, 
			ONE_MINUS_SRC_ALPHA, 
			DST_ALPHA, 
			ONE_MINUS_DST_ALPHA, 
			CONSTANT_COLOR, 
			ONE_MINUS_CONSTANT_COLOR, 
			CONSTANT_ALPHA,
			ONE_MINUS_CONSTANT_ALPHA, 
			SRC_ALPHA_SATURATE, 
			SRC1_COLOR, 
			ONE_MINUS_SRC1_COLOR, 
			SRC1_ALPHA, 
			ONE_MINUS_SRC1_ALPHA
		};
	private:
		BOOLEAN mEnabled;
		BlendFunction mSourceFunction;
		BlendFunction mDestFunction;
	public:
        
		AlphaBlend();
		virtual ~AlphaBlend();
        
		BOOLEAN IsEnabled() const;
		void SetEnabled(const BOOLEAN &enabled);
		BlendFunction GetSourceFunction() const;
		void SetSourceFunction(const BlendFunction& function);
		BlendFunction GetDestinationFunction() const;
		void SetDestinationFunction(const BlendFunction& function);
        
		virtual void Set(RenderingDevice* device) override;
		virtual RenderStateNames GetRenderStateName() { return RenderState::ALPHA_BLEND; }
	};
}

#else
namespace bde{
	class AlphaBlend;
} // namespace bde
#endif
