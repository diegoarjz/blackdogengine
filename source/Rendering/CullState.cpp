#include "CullState.h"
#include "RenderingDevice.h"

namespace bde{
	CullState::CullState(){
		mEnabled = true;
        mCullFace = CULL_BACK;
        mFrontFace = CCW;
	}
	
	CullState::~CullState(){
		
	}
    
	BOOLEAN CullState::IsEnabled() const{
		return mEnabled;
	}
	
	void CullState::SetEnabled(const BOOLEAN &enabled){
		mEnabled = enabled;
	}
	
	CullState::FrontFace CullState::GetFrontFace() const{
		return mFrontFace;
	}
	
	void CullState::SetFrontFace(const CullState::FrontFace &frontFace){
		mFrontFace = frontFace;
	}
	
	CullState::CullFace CullState::GetCullFace() const{
		return mCullFace;
	}
	
	void CullState::SetCullFace(const CullState::CullFace &cullFace){
		mCullFace = cullFace;
	}
	
	void CullState::Set(RenderingDevice* device){
		device->SetCullState(shared_from_this());
	}
} // namespace bde