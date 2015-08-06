#include "AlphaBlend.h"
#include "RenderingDevice.h"

namespace bde{
	
	AlphaBlend::AlphaBlend(){
		mEnabled = false;
        mSourceFunction = ONE;
        mDestFunction = ONE;
	}

	AlphaBlend::~AlphaBlend(){
		
	}
	
	BOOLEAN AlphaBlend::IsEnabled() const{
		return mEnabled;
	}
	
	void AlphaBlend::SetEnabled(const BOOLEAN &enabled){
		mEnabled = enabled;
	}
	
	AlphaBlend::BlendFunction AlphaBlend::GetSourceFunction() const{
		return mSourceFunction;
	}
	
	void AlphaBlend::SetSourceFunction(const AlphaBlend::BlendFunction& function){
		mSourceFunction = function;
	}
	
	AlphaBlend::BlendFunction AlphaBlend::GetDestinationFunction() const{
		return mDestFunction;
	}
	
	void AlphaBlend::SetDestinationFunction(const AlphaBlend::BlendFunction& function){
		mDestFunction = function;
	}
	
	void AlphaBlend::Set(RenderingDevice* device){
		device->SetAlphaBlend(shared_from_this());
	}
} /* bde */