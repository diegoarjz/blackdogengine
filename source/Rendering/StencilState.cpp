#include "StencilState.h"
#include "RenderingDevice.h"

namespace bde{
	StencilState::StencilState(){
		mEnabled = false;
		mFunction = ALWAYS;
		mReferenceValue = 0;
		mMask = 0xFF;
		
		mStencilFails = KEEP;
		mStencilPassesDepthFails = KEEP;
		mStencilDepthPass = KEEP;
		
		mStencilMask = 0xFF;
	}
	
	StencilState::~StencilState(){
		
	}
	
	BOOLEAN StencilState::IsEnabled() const{
		return mEnabled;
	}
	
	void StencilState::SetEnabled(const BOOLEAN &enabled){
		mEnabled = enabled;
	}
	
	StencilState::StencilFunction StencilState::GetStencilFunction()const{
		return mFunction;
	}
	
	void StencilState::SetStencilFunction(const StencilState::StencilFunction &function){
		mFunction = function;
	}
	
	I32 StencilState::GetReferenceValue() const{
		return mReferenceValue;
	}
	
	void StencilState::SetReferenceValue(const I32 &referenceValue){
		mReferenceValue = referenceValue;
	}
	
	U32 StencilState::GetMask()const{
		return mMask;
	}
	
	void StencilState::SetMask(const U32 &mask){
		mMask = mask;
	}
	
	StencilState::StencilOperation StencilState::GetStencilFailsOp()const{
		return mStencilFails;
	}
	
	void StencilState::SetStencilFailsOp(const StencilState::StencilOperation &op){
		mStencilFails = op;
	}
	
	StencilState::StencilOperation StencilState::GetStencilPassesDepthFailsOp()const{
		return mStencilPassesDepthFails;
	}
	
	void StencilState::SetStencilPassesDepthFailsOp(const StencilState::StencilOperation &op){
		mStencilPassesDepthFails = op;
	}
	
	StencilState::StencilOperation StencilState::GetStencilDepthPassOp() const{
		return mStencilDepthPass;
	}
	
	void StencilState::SetStencilDepthPassOp(const StencilState::StencilOperation &op){
		mStencilDepthPass = op;
	}
	
	U32 StencilState::GetStencilMask()const{
		return mStencilMask;
	}
	
	void StencilState::SetStencilMask(const U32 &mask){
		mStencilMask = mask;
	}
	
	void StencilState::Set(RenderingDevice* device){
		device->SetStencilState(shared_from_this());
	}
} /* bde */