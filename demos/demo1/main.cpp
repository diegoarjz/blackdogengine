#include <iostream>
#include <fstream>

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
#include "../../source/Rendering/SetCameraRenderTask.h"
#include "../../source/Rendering/ShaderUniform.h"
#include "../../source/TransformationSubsystem.h"
#include "../../source/CameraSubsystem.h"
#include "../../source/GameObject.h"

using namespace bde;

std::string read_file(const std::string &path){
    std::ifstream t(path);
    std::string str;
    
    t.seekg(0, std::ios::end);
    str.reserve(t.tellg());
    t.seekg(0, std::ios::beg);
    
    str.assign(std::istreambuf_iterator<char>(t),
               std::istreambuf_iterator<char>());
    
    return str;
}

ShaderProgramPtr createShaderProgram(){
	// Load Shader
	ShaderPtr vertShader = std::make_shared<Shader>(Shader::ShaderType::Vertex);
	vertShader->SetSource( read_file("shaders/vertex.vert") );
            
	ShaderPtr fragShader = std::make_shared<Shader>(Shader::ShaderType::Fragment);
	fragShader->SetSource( read_file("shaders/fragment.frag") );
            
	ShaderProgramPtr shaderProgram = std::make_shared<ShaderProgram>();
	shaderProgram->SetShader(Shader::ShaderType::Vertex, vertShader);
	shaderProgram->SetShader(Shader::ShaderType::Fragment, fragShader);
	shaderProgram->SetOutputName(ShaderProgram::ShaderOutputType::ScreenBuffer, "outColor");
            
	shaderProgram->BindSemanticsToName(ShaderAttribute::Semantics::ModelMatrix, "model");
	shaderProgram->BindSemanticsToName(ShaderAttribute::Semantics::ViewMatrix, "view");
	shaderProgram->BindSemanticsToName(ShaderAttribute::Semantics::ProjectionMatrix, "projection");
	
	std::shared_ptr<DepthBuffer> db = std::make_shared<DepthBuffer>();
	db->SetEnabled(true);
	db->SetDepthFunction( DepthBuffer::LESS );
	shaderProgram->SetRenderState(db);
	
	std::shared_ptr<CullState> cull = std::make_shared<CullState>();
	cull->SetEnabled(true);
	cull->SetCullFace(CullState::CULL_BACK);
	cull->SetFrontFace(CullState::CCW);
	shaderProgram->SetRenderState(cull);
	
	std::shared_ptr<AlphaBlend> alpha = std::make_shared<AlphaBlend>();
	alpha->SetEnabled(true);
	shaderProgram->SetRenderState(alpha);
	
	return shaderProgram;
}

class GameLoop : public Thread{

    protected:

        virtual void run() override{
            mRenderPool->NotifyUpdateReady();
            mRenderPool->WaitForRenderReady();

            float r = 0;
            float g = 0;
            float b = 0;
            
            TransformationSubsystem transformSS;
            CameraSubsystem cameraSS;
            
            // Create Game Object
            GameObjectPtr root = std::make_shared<GameObject>();
            root->SetComponent<TransformComponent>(transformSS.CreateComponent());
            auto rootTransform = root->GetComponent<TransformComponent>();
            
            GameObjectPtr go = std::make_shared<GameObject>();
            go->SetComponent<TransformComponent>(transformSS.CreateComponent());
            auto transformComponent = go->GetComponent<TransformComponent>();
            transformComponent->SetParentTransform(rootTransform);
			transformComponent->SetPosition(0,-1,-10);
            
            GameObjectPtr camGO = std::make_shared<GameObject>();
            camGO->SetComponent<TransformComponent>(transformSS.CreateComponent());
            CameraPtr camera = cameraSS.CreateComponent();
            camGO->SetComponent<Camera>(camera);
            
            camera->SetFrustum(30, 1, 0.001, 1000);
            
            auto shaderProgram = createShaderProgram();
            auto loadShader = std::make_shared<LoadShaderRenderTask>(shaderProgram);
            auto setShader  = std::make_shared<SetShaderRenderTask>(shaderProgram);
            
            mRenderPool->Push(loadShader);
            mRenderPool->Push(setShader);
            
            // Load Geometry
            std::vector<Vertex> vertices = {
                {Vector3f({-1,-1,0}), Vector3f({1,0,0})},
                {Vector3f({ 1,-1,0}), Vector3f({1,0,0})},
                {Vector3f({ 0, 1,0}), Vector3f({1,0,0})},
                
                {Vector3f({-1,-1,0}), Vector3f({0,1,0})},
                {Vector3f({ 0, 1,0}), Vector3f({0,1,0})},
                {Vector3f({ 0,-1,1}), Vector3f({0,1,0})},
                
                {Vector3f({ 0,-1,1}), Vector3f({0,0,1})},
                {Vector3f({ 0, 1,0}), Vector3f({0,0,1})},
                {Vector3f({ 1,-1,0}), Vector3f({0,0,1})},
                
                {Vector3f({-1,-1,0}), Vector3f({1,1,0})},
                {Vector3f({ 0,-1,1}), Vector3f({1,1,0})},
                {Vector3f({ 1,-1,0}), Vector3f({1,1,0})},
            };

            U32 els[] = {
                0,  1,  2,
                3,  4,  5,
                6,  7,  8,
                9, 10, 11
            };
            ElementDataSourcePtr elements = std::make_shared<ElementDataSource>(els, PrimitiveType::Triangles, 4, 12);
            auto vertexDataSources = create_vertex_data_sources<Vertex>(vertices);
            auto geometry = std::make_shared<Geometry>(&(vertices[0]), 12, vertexDataSources, elements);
            
            // Draw Geometry
            auto draw = std::make_shared<DrawGeometryRenderTask>(geometry);
            
            // Set camera
            auto setCamera = std::make_shared<SetCameraRenderTask>(camera);
            mRenderPool->Push(setCamera);
            
            // Material
            MaterialPtr material = std::make_shared<Material>(shaderProgram);
//            auto colorUniform = material->GetUniform<ColorRGB>("color");
            auto setMaterial = std::make_shared< SetMaterialRenderTask >(material, go);

            auto loadGeometry = std::make_shared<LoadGeometryRenderTask>(geometry);
            mRenderPool->Push(loadGeometry);

            Time start;
            Time last;
            bool loaded = false;
            while(!mShouldStop){
                Time current;
                TimeDifference elapsed = current - last;
                last = current;

                // transformComponent->SetPosition(cos(current.GetTimestamp()/1000),
//                                                 sin(current.GetTimestamp()/1000),
//                                cos(current.GetTimestamp()/1000)-10);
                transformComponent->Roll(0.001*elapsed.mTimeDifference);

                
                transformSS.Update( elapsed.mTimeDifference );
                cameraSS.Update( elapsed.mTimeDifference );
                
                r = sin(current.GetTimestamp()/1000) * sin(current.GetTimestamp()/1000);
                g = cos(current.GetTimestamp()/1000) * cos(current.GetTimestamp()/1000);
                b = tan(current.GetTimestamp()/1000) * tan(current.GetTimestamp()/1000);
                
//                colorUniform->SetValue( ColorRGB(r,g,b) );
                
                mRenderPool->Push( setMaterial );
                mRenderPool->Push( draw );
                
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
