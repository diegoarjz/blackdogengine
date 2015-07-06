#include <iostream>

#include "../../source/Rendering/Renderer.h"
#include "../../source/Debug/Logger.h"
#include "../../source/Rendering/GLFW/GLFWRenderingDevice.h"
#include "../../source/Rendering/SetBackgroundColorRenderTask.h"
#include "../../source/Rendering/LoadGeometryRenderTask.h"
#include "../../source/System/Thread.h"
#include "../../source/System/Time.h"
#include "../../source/Geometry/Geometry.h"
#include "../../source/Geometry/ElementDataSource.h"
#include "../../source/Geometry/create_vertex_data_sources.h"
#include "../../source/Rendering/ShaderProgram.h"
#include "../../source/Rendering/LoadShaderRenderTask.h"
#include "../../source/Rendering/SetShaderRenderTask.h"
#include "../../source/Rendering/DrawGeometryRenderTask.h"
#include "../../source/Rendering/SetMaterialRenderTask.h"

using namespace bde;

std::string vertShaderSource ="#version 150 \n \
in vec3 position; \n \
void main() \n \
{ \n \
    gl_Position = vec4(position, 1.0); \n \
}";

std::string fragShaderSource = "#version 150 \n \
\n \
out vec4 outColor; \n \
uniform vec3 color; \n \
void main() \n \
{ \n \
    outColor = vec4(color, 1.0); \n \
}";

class GameLoop : public Thread{

    protected:

        virtual void run() override{
            mRenderPool->NotifyUpdateReady();
            mRenderPool->WaitForRenderReady();

            float r = 0;
            float g = 0;
            float b = 0;
            
            // Load Shader
            ShaderPtr vertShader = std::make_shared<Shader>(Shader::ShaderType::Vertex);
            vertShader->SetSource( vertShaderSource );
            
            ShaderPtr fragShader = std::make_shared<Shader>(Shader::ShaderType::Fragment);
            fragShader->SetSource( fragShaderSource );
            
            ShaderProgramPtr shaderProgram = std::make_shared<ShaderProgram>();
            shaderProgram->SetShader(Shader::ShaderType::Vertex, vertShader);
            shaderProgram->SetShader(Shader::ShaderType::Fragment, fragShader);
            shaderProgram->SetOutputName(ShaderProgram::ShaderOutputType::ScreenBuffer, "outColor");
            shaderProgram->CustomUniforms().push_back( std::make_shared<ShaderUniform>(ShaderUniform::ShaderUniformType::ColorRGBUniform, "color") );
            
            auto loadShader = std::make_shared<LoadShaderRenderTask>(shaderProgram);
            auto setShader  = std::make_shared<SetShaderRenderTask>(shaderProgram);
            
            mRenderPool->Push(loadShader);
            mRenderPool->Push(setShader);
            
            // Load Geometry
            std::vector<Vertex> vertices;
            Vertex v1; v1.mPosition = Vector3(-1,-1,0);
            Vertex v2; v2.mPosition = Vector3( 1,-1,0);
            Vertex v3; v3.mPosition = Vector3( 0, 1,0);
            vertices.push_back(v1);
            vertices.push_back(v2);
            vertices.push_back(v3);
            
            U32 els[] = {0,1,2};
            ElementDataSourcePtr elements = std::make_shared<ElementDataSource>(els, PrimitiveType::Triangles, 1, 3);
            auto vertexDataSources = create_vertex_data_sources<Vertex>(vertices);
            auto geometry = std::make_shared<Geometry>(&(vertices[0]), 3, vertexDataSources, elements);
            
            // Draw Geometry
            auto draw = std::make_shared<DrawGeometryRenderTask>(geometry);
            
            // Material
            MaterialPtr material = std::make_shared<Material>(shaderProgram);
            auto colorUniform = material->GetUniform<ColorRGB>("color");
            auto setMaterial = std::make_shared< SetMaterialRenderTask >(material);

            Time start;
            Time last;
            bool loaded = false;
            while(!mShouldStop){
                Time current;
                TimeDifference elapsed = current - last;
                last = current;

                r = sin(current.GetTimestamp()/1000) * sin(current.GetTimestamp()/1000);
                g = cos(current.GetTimestamp()/1000) * cos(current.GetTimestamp()/1000);
                b = tan(current.GetTimestamp()/1000) * tan(current.GetTimestamp()/1000);
                
                colorUniform->SetValue( ColorRGB(r,g,b) );
                
                if((current-start).mTimeDifference > 1000 && !loaded){
                    auto loadGeometry = std::make_shared<LoadGeometryRenderTask>(geometry);
                    mRenderPool->Push(loadGeometry);
                    loaded = true;
                }
                if(loaded){
                    mRenderPool->Push( draw );
                    mRenderPool->Push( setMaterial );
                }
                
                mRenderPool->WaitForRenderDone();
                mRenderPool->SwapRenderQueues();
                mRenderPool->NotifySwapDone();
                
                //usleep(100000);
            }
        }

    public:

        RenderPoolPtr mRenderPool;
        bool          mShouldStop;
};

int main(int argc, char *argv[]){

    LoggerPtr logger = std::make_shared<Logger>(std::cout);
    Logger::SetLoggerForLevel(Logger::LoggerLevel::Info, logger);
    Logger::SetLoggerForLevel(Logger::LoggerLevel::Error, logger);

    LOG_INFO("Program Start");

    try{
        RendererPtr r = std::make_shared<Renderer>();
        GLFWRenderingDevicePtr renderingDevice = std::make_shared<GLFWRenderingDevice>();
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
