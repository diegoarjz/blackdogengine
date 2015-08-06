#ifndef CULL_STATE_H_
#define CULL_STATE_H_

#include "../DataTypes.h"
#include "RenderState.h"

namespace bde{
	class CullState : public RenderState, public std::enable_shared_from_this<CullState>{
	public:
		enum FrontFace{
			CW,
			CCW
		};
        
		enum CullFace{
			CULL_FRONT,
			CULL_BACK,
			CULL_FRONT_BACK
		};
	private:
		bool mEnabled;
		FrontFace mFrontFace;
		CullFace mCullFace;
		
	public:
		CullState();
		virtual ~CullState();
        
		BOOLEAN IsEnabled() const;
		void SetEnabled(const BOOLEAN &enabled);
		FrontFace GetFrontFace() const;
		void SetFrontFace(const FrontFace &frontFace);
		CullFace GetCullFace() const;
		void SetCullFace(const CullFace &cullFace);
		
		virtual void Set(RenderingDevice* device) override;
		virtual RenderStateNames GetRenderStateName() override { return RenderState::CULL; }
	}; // class CullState
} // namespace bde

#else
namespace bde {
	class CullState;
} // namespace bde
#endif