#ifndef STENCIL_STATE_H_
#define STENCIL_STATE_H_

#include "../DataTypes.h"
#include "RenderState.h"

namespace bde{
	class StencilState : public RenderState, public std::enable_shared_from_this<StencilState>{
	public:
		enum StencilFunction{
			NEVER,
			LESS, 
			LEQUAL,
			GREATER,
			GEQUAL,
			EQUAL,
			NOTEQUAL,
			ALWAYS
		};
		
		enum StencilOperation{
			 KEEP,
			 ZERO,
			 REPLACE,
			 INCR,
			 INCR_WRAP,
			 DECR,
			 DECR_WRAP,
			 INVERT
		};
	private:
		BOOLEAN mEnabled;
		StencilFunction mFunction;
		I32 mReferenceValue;
		U32 mMask;
		
		StencilOperation mStencilFails;
		StencilOperation mStencilPassesDepthFails;
		StencilOperation mStencilDepthPass;
		
		U32 mStencilMask;
	public:
		StencilState();
		virtual ~StencilState();
		
		BOOLEAN IsEnabled() const;
		void SetEnabled(const BOOLEAN &enabled);
		StencilFunction GetStencilFunction()const;
		void SetStencilFunction(const StencilFunction &function);
		I32 GetReferenceValue() const;
		void SetReferenceValue(const I32 &referenceValue);
		U32 GetMask()const;
		void SetMask(const U32 &mask);
		StencilOperation GetStencilFailsOp()const;
		void SetStencilFailsOp(const StencilOperation &op);
		StencilOperation GetStencilPassesDepthFailsOp()const;
		void SetStencilPassesDepthFailsOp(const StencilOperation &op);
		StencilOperation GetStencilDepthPassOp() const;
		void SetStencilDepthPassOp(const StencilOperation &op);
		U32 GetStencilMask()const;
		void SetStencilMask(const U32 &mask);
		
		virtual void Set(RenderingDevice* device) override;
		virtual RenderStateNames GetRenderStateName() override { return RenderState::STENCIL_STATE; }
	};
} /* bde */

#else

#endif