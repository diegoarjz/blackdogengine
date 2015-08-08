#include "BasicApplication.h"

#include "Rendering/GLFW/GLFWRenderingDevice.h"

namespace bde
{
	BasicApplication::BasicApplication (){
		
	}
	
	BasicApplication::~BasicApplication (){
		
	}

	bool BasicApplication::Initialize(){
		mBlackDogEngine = BlackDogEngine::Create();
		
        mRenderer = std::make_shared<Renderer>();
        GLFWRenderingDevicePtr renderingDevice = std::make_shared<GLFWRenderingDevice>();
        mRenderer->SetRenderingDevice(renderingDevice);
		mRenderPool = mRenderer->GetRenderPool();
		
		return true;
	}
	
	bool BasicApplication::LoadAssets(){
		
		return true;
	}
	
	void BasicApplication::UnloadAssets(){
		
	}
	
	void BasicApplication::Destroy(){
		
	}
	
	void BasicApplication::Update(const TimeDifference &dT){
		mBlackDogEngine->Update(dT.mTimeDifference);
	}
	
	int BasicApplication::Run(){
		// Start the renderer in the main thread
		mRenderer->Start();

		// and the update loop in another thread.
		Start();
		
		return 0;
	}
	
	void BasicApplication::Stop(){
		mShouldStop = true;
		Join();
	}
	
	void BasicApplication::run() {
        Time start;
        Time last;
        bool loaded = false;
        while(!mShouldStop){
            Time current;
            TimeDifference elapsed = current - last;
            last = current;

            Update(elapsed);
            
            mRenderPool->WaitForRenderDone();
            mRenderPool->SwapRenderQueues();
            mRenderPool->NotifySwapDone();
            //usleep(100000);
        }
	}
} // namespace bde