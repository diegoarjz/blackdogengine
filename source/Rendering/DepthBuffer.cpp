#include "DepthBuffer.h"
#include "RenderingDevice.h"

namespace bde {
    DepthBuffer::DepthBuffer(){
        mEnabled = true;
        mFunction = LESS;
    }
    
	DepthBuffer::~DepthBuffer(){
		
	}
	
	BOOLEAN DepthBuffer::IsEnabled() const{
		return mEnabled;
	}
	
	void DepthBuffer::SetEnabled(const BOOLEAN &enabled){
		mEnabled = enabled;
	}
	
	DepthBuffer::DepthFunction DepthBuffer::GetDepthFunction() const{
		return mFunction;
	}
	
	void DepthBuffer::Set(RenderingDevice* device){
		device->SetDepthBuffer(shared_from_this());
	}
	
	void DepthBuffer::SetDepthFunction(const DepthBuffer::DepthFunction &function){
		mFunction = function;
	}
} // namespace bde