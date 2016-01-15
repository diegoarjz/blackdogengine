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

#define degreesToRadians(x) x*(3.141592f/180.0f)

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

ShaderProgramPtr loadShaderProgram(){
	ShaderPtr vertShader = std::make_shared<Shader>(Shader::ShaderType::Vertex, 
													read_file("shaders/vertex.vert"));
	ShaderPtr fragShader = std::make_shared<Shader>(Shader::ShaderType::Fragment, 
													read_file("shaders/fragment.frag") );
	
	ShaderProgramPtr shaderProgram = std::make_shared<ShaderProgram>(vertShader, fragShader);
	shaderProgram->SetOutputName(ShaderProgram::ShaderOutputType::ScreenBuffer, "outColor");
	
	shaderProgram->BindSemanticsToName(ShaderAttribute::Semantics::ModelMatrix, "model");
	shaderProgram->BindSemanticsToName(ShaderAttribute::Semantics::ViewMatrix, "view");
	shaderProgram->BindSemanticsToName(ShaderAttribute::Semantics::ProjectionMatrix, "projection");
	
	shaderProgram->AddShaderUniform( std::make_shared<ShaderUniform<float>>("tintFactor") );
	
	return shaderProgram;
}

ShaderProgramPtr createCubeShaderProgram(){
	ShaderProgramPtr shaderProgram = loadShaderProgram();
	
	std::shared_ptr<DepthBuffer> db = std::make_shared<DepthBuffer>();
	db->SetEnabled(true);
	shaderProgram->SetRenderState(db);
	
	std::shared_ptr<StencilState> stencil = std::make_shared<StencilState>();
	stencil->SetEnabled(false);
	
	shaderProgram->SetRenderState(stencil);
	
	return shaderProgram;
}

ShaderProgramPtr createReflexCubeShaderProgram(){
	// Load Shader
	ShaderProgramPtr shaderProgram = loadShaderProgram();
	
	std::shared_ptr<DepthBuffer> db = std::make_shared<DepthBuffer>();
	db->SetEnabled(true);
	shaderProgram->SetRenderState(db);
	
	std::shared_ptr<StencilState> stencil = std::make_shared<StencilState>();
	stencil->SetEnabled(true);
	stencil->SetStencilFunction( StencilState::EQUAL );
	stencil->SetReferenceValue( 1 );
	
	std::shared_ptr<CullState> cull = std::make_shared<CullState>();
	cull->SetEnabled(false);
	shaderProgram->SetRenderState(cull);
	
	shaderProgram->SetRenderState(stencil);
	
	return shaderProgram;
}

ShaderProgramPtr createFloorShaderProgram(){
	// Load Shader
	ShaderProgramPtr shaderProgram = loadShaderProgram();
	
	std::shared_ptr<StencilState> stencil = std::make_shared<StencilState>();
	stencil->SetEnabled(true);
	stencil->SetStencilFunction( StencilState::ALWAYS );
	stencil->SetStencilDepthPassOp( StencilState::REPLACE );
	stencil->SetReferenceValue( 1 );
	
	shaderProgram->SetRenderState(stencil);
	
	std::shared_ptr<DepthBuffer> db = std::make_shared<DepthBuffer>();
	db->SetEnabled(false);
	shaderProgram->SetRenderState(db);
	
	return shaderProgram;
}

GeometryPtr createCube(){
	
	std::vector<Vertex> vertices({
		// Bottom Face (Red)
		{Vector3<>(-1,-1, 1), Vector3<>(1,0,0)}, // index: 0
		{Vector3<>(-1,-1,-1), Vector3<>(1,0,0)}, // index: 1
		{Vector3<>( 1,-1,-1), Vector3<>(1,0,0)}, // index: 2
		{Vector3<>( 1,-1, 1), Vector3<>(1,0,0)}, // index: 3
		
		// Front Face (Blue)
		{Vector3<>(-1,-1, 1), Vector3<>(0,0,1)}, // index: 4
		{Vector3<>( 1,-1, 1), Vector3<>(0,0,1)}, // index: 5
		{Vector3<>( 1, 1, 1), Vector3<>(0,0,1)}, // index: 6
		{Vector3<>(-1, 1, 1), Vector3<>(0,0,1)}, // index: 7
		
		// Right Face (Green)
		{Vector3<>( 1,-1, 1), Vector3<>(0,1,0)}, // index: 8
		{Vector3<>( 1,-1,-1), Vector3<>(0,1,0)}, // index: 9
		{Vector3<>( 1, 1,-1), Vector3<>(0,1,0)}, // index: 10
		{Vector3<>( 1, 1, 1), Vector3<>(0,1,0)}, // index: 11
		
		// Back Face (Yellow)
		{Vector3<>( 1,-1,-1), Vector3<>(1,1,0)}, // index: 12
		{Vector3<>(-1,-1,-1), Vector3<>(1,1,0)}, // index: 13
		{Vector3<>(-1, 1,-1), Vector3<>(1,1,0)}, // index: 14
		{Vector3<>( 1, 1,-1), Vector3<>(1,1,0)}, // index: 15
		
		// Left Face (Purple)
		{Vector3<>(-1,-1, 1), Vector3<>(1,0,1)}, // index: 16
		{Vector3<>(-1, 1, 1), Vector3<>(1,0,1)}, // index: 17
		{Vector3<>(-1, 1,-1), Vector3<>(1,0,1)}, // index: 18
		{Vector3<>(-1,-1,-1), Vector3<>(1,0,1)}, // index: 19
		
		// Top Face (Blueish green)
		{Vector3<>(-1, 1, 1), Vector3<>(0,1,1)}, // index: 20
		{Vector3<>( 1, 1, 1), Vector3<>(0,1,1)}, // index: 21
		{Vector3<>( 1, 1,-1), Vector3<>(0,1,1)}, // index: 22
		{Vector3<>(-1, 1,-1), Vector3<>(0,1,1)}, // index: 23
	});
	
	U32 els[] = {
		// Bottom Face
		0,1,3, 1,2,3,
		// Front Face
		4,5,7, 5,6,7,
		// Right Face
		8,9,11, 9,10,11,
		// Back Face
		12,13,15, 13,14,15,
		// Left Face
		16,17,19, 17,18,19,
		// Top Face
		20,21,23, 21,22,23
	};
	
    ElementDataSourcePtr elements = std::make_shared<ElementDataSource>(els, PrimitiveType::Triangles, 12, 36);
    auto vertexDataSources = create_vertex_data_sources<Vertex>(vertices);
    auto geometry = std::make_shared<Geometry>(&(vertices[0]), 24, vertexDataSources, elements);
	
	return geometry;
}

GeometryPtr createFloor(const float &size){
	std::vector<Vertex> vertices({
		{Vector3<>( size, 0, size), Vector3<>(0.1,0.1,0.1)},
		{Vector3<>( size, 0,-size), Vector3<>(0.1,0.1,0.1)},
		{Vector3<>(-size, 0,-size), Vector3<>(0.1,0.1,0.1)},
		{Vector3<>(-size, 0, size), Vector3<>(0.1,0.1,0.1)}
	});
	
	U32 els[]={0,1,3, 1,2,3};

    ElementDataSourcePtr elements = std::make_shared<ElementDataSource>(els, PrimitiveType::Triangles, 2, 6);
    auto vertexDataSources = create_vertex_data_sources<Vertex>(vertices);
    auto geometry = std::make_shared<Geometry>(&(vertices[0]), 4, vertexDataSources, elements);
	
	return geometry;	
}

class GameLoop : public Thread{

    protected:

        virtual void run() override{
            mRenderPool->NotifyUpdateReady();
            mRenderPool->WaitForRenderReady();
			
			TransformationSubsystem transformSS;
            CameraSubsystem cameraSS;
            
            // Create Game Object
            GameObjectPtr root = std::make_shared<GameObject>();
            root->SetComponent<TransformComponent>(transformSS.CreateComponent());
            auto rootTransform = root->GetComponent<TransformComponent>();
            
            GameObjectPtr cubeGO = std::make_shared<GameObject>();
            cubeGO->SetComponent<TransformComponent>(transformSS.CreateComponent());
            auto transformComponent = cubeGO->GetComponent<TransformComponent>();
            transformComponent->SetParentTransform(rootTransform);
			transformComponent->SetPosition(0,0,-15);
			
            GameObjectPtr floorGO = std::make_shared<GameObject>();
            floorGO->SetComponent<TransformComponent>(transformSS.CreateComponent());
            auto floorTransformComponent = floorGO->GetComponent<TransformComponent>();
            floorTransformComponent->SetParentTransform(rootTransform);
			floorTransformComponent->SetPosition(0,-1,-15);
			
			GameObjectPtr reflexCubeGO = std::make_shared<GameObject>();
            reflexCubeGO->SetComponent<TransformComponent>(transformSS.CreateComponent());
            auto reflexTransformComponent = reflexCubeGO->GetComponent<TransformComponent>();
            reflexTransformComponent->SetParentTransform(rootTransform);
			reflexTransformComponent->SetPosition(0,-2,-15);
			reflexTransformComponent->SetScale(1,-1,1);
            
            GameObjectPtr camGO = std::make_shared<GameObject>();
			auto camTransform = transformSS.CreateComponent();
            camGO->SetComponent<TransformComponent>(camTransform);
			camTransform->Pitch(degreesToRadians(-10));
			camTransform->SetPosition(0,3,0);
            CameraPtr camera = cameraSS.CreateComponent();
            camGO->SetComponent<Camera>(camera);
            
            camera->SetFrustum(30, 1, 0.001, 1000);
			
            auto cubeGeometry = createCube();
			auto floorGeometry = createFloor(5);
            
			auto bgColor = std::make_shared<SetBackgroundColorRenderTask>(ColorRGB(1,1,1));
			mRenderPool->Push(bgColor);
			
            // Draw Geometry
            auto drawCube = std::make_shared<DrawGeometryRenderTask>(cubeGeometry);
			auto drawFloor = std::make_shared<DrawGeometryRenderTask>(floorGeometry);
            
            // Set camera
            auto setCamera = std::make_shared<SetCameraRenderTask>(camera);
            mRenderPool->Push(setCamera);
            
            // Cube Material
            auto shaderProgram = createCubeShaderProgram();
            auto loadShader = std::make_shared<LoadShaderRenderTask>(shaderProgram);
			mRenderPool->Push(loadShader);
			
            MaterialPtr material = std::make_shared<Material>(shaderProgram);
			material->GetUniform<float>("tintFactor")->SetValue(1.0f);
            auto setMaterial = std::make_shared< SetMaterialRenderTask >(material, cubeGO);
			
			// Floor Material
			auto floorShaderProgram = createFloorShaderProgram();
			auto loadFloorShaderProgram = std::make_shared<LoadShaderRenderTask>(floorShaderProgram);
			mRenderPool->Push(loadFloorShaderProgram);
			
			MaterialPtr floorMaterial = std::make_shared<Material>(floorShaderProgram);
			floorMaterial->GetUniform<float>("tintFactor")->SetValue(1.0f);
			auto setFloorMaterial = std::make_shared< SetMaterialRenderTask >(floorMaterial, floorGO);
			
			// Reflex Material
            auto reflexShaderProgram = createReflexCubeShaderProgram();
			auto loadReflexShader = std::make_shared<LoadShaderRenderTask>(reflexShaderProgram);
			mRenderPool->Push(loadReflexShader);
			
            MaterialPtr reflexMaterial = std::make_shared<Material>(reflexShaderProgram);
			reflexMaterial->GetUniform<float>("tintFactor")->SetValue(0.5f);
            auto setReflexMaterial = std::make_shared< SetMaterialRenderTask >(reflexMaterial, reflexCubeGO);

            auto loadCube = std::make_shared<LoadGeometryRenderTask>(cubeGeometry);
			auto loadFloor = std::make_shared<LoadGeometryRenderTask>(floorGeometry);
            mRenderPool->Push(loadCube);
			mRenderPool->Push(loadFloor);

            Time start;
            Time last;
            bool loaded = false;
            while(!mShouldStop){
                Time current;
                TimeDifference elapsed = current - last;
                last = current;

                transformComponent->Roll(0.001*elapsed.mTimeDifference);
				reflexTransformComponent->Roll(0.001*elapsed.mTimeDifference);
                
                transformSS.Update( elapsed.mTimeDifference );
                cameraSS.Update( elapsed.mTimeDifference );
				
				mRenderPool->Push( setFloorMaterial );
				mRenderPool->Push( drawFloor );
				
				mRenderPool->Push( setReflexMaterial );
				mRenderPool->Push( drawCube );
				
                mRenderPool->Push( setMaterial );
                mRenderPool->Push( drawCube );
                
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
