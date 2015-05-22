#include <iostream>

#include "../../source/Rendering/Renderer.h"
#include "../../source/Debug/Logger.h"
#include "../../source/Rendering/GLFW/GLFWRenderingDevice.h"
#include "../../source/Rendering/SetBackgroundColorRenderTask.h"
#include "../../source/System/Thread.h"
#include "../../source/System/Time.h"

#include <unistd.h>

class GameLoop : public bde::Thread{

    protected:

        virtual void run() override{
            float r = 0;
            float g = 0;
            float b = 0;

            bde::Time last;
            while(!mShouldStop){
                bde::Time current;
                bde::TimeDifference elapsed = current - last;
                last = current;

                r = sin(current.GetTimestamp()/1000) * sin(current.GetTimestamp()/1000);
                g = cos(current.GetTimestamp()/1000) * cos(current.GetTimestamp()/1000);
                b = tan(current.GetTimestamp()/1000) * tan(current.GetTimestamp()/1000);

                mRenderPool->Push( std::make_shared<bde::SetBackgroundColorRenderTask>( bde::ColorRGB(r,g,b) ) );
                mRenderPool->FinishFrame();

                usleep( 1/30 * 1000000 );
            }
        }

    public:

        bde::RenderPoolPtr mRenderPool;
        bool               mShouldStop;
};

int main(int argc, char *argv[]){

    bde::LoggerPtr logger = std::make_shared<bde::Logger>(std::cout);
    bde::Logger::SetLoggerForLevel(bde::Logger::LoggerLevel::Info, logger);
    bde::Logger::SetLoggingLevel(bde::Logger::LoggerLevel::Info);
    LOG_INFO("Program Start");

    try{
        bde::RendererPtr r = std::make_shared<bde::Renderer>();
        bde::GLFWRenderingDevicePtr renderingDevice = std::make_shared<bde::GLFWRenderingDevice>();
        r->SetRenderingDevice(renderingDevice);

        GameLoop g;
        g.mRenderPool = r->GetRenderPool();
        g.Start();

        r->Start();
        g.mShouldStop = true;

        g.Join();
    }
    catch(...){
        std::cout << "Error" << std::endl;
    }

    return 0;
}
