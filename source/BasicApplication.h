#ifndef BASIC_APPLICATION_H_
#define BASIC_APPLICATION_H_

#include "BlackDogEngine.h"
#include "Rendering/Renderer.h"
#include "System/Thread.h"
#include "System/Time.h"

namespace bde{
	
	class BasicApplication : public Thread{
	private:
		BlackDogEnginePtr mBlackDogEngine;
		RendererPtr mRenderer;
		RenderPoolPtr mRenderPool;
		BOOLEAN mShouldStop;
	public:
		BasicApplication ();
		virtual ~BasicApplication ();
	
		virtual bool Initialize();
		virtual bool LoadAssets();
		virtual void UnloadAssets();
		virtual void Destroy();
		
		virtual int Run();
		virtual void Stop();
		virtual void Update(const TimeDifference &dT);
		
	protected:
		
		virtual void run() override;
	}; // class BasicApplication
} // namespace bde
#else
namespace bde{
	class BasicApplication;
} // namespace bde
#endif