#include "GLFWRenderingDevice.h"

#include <OpenGL/GL3.h>

#include "../../Debug/Logger.h"
#include "../ShaderProgram.h"
#include "../Material.h"
#include "../ShaderUniform.h"
#include "../ShaderUniformValue.h"

namespace bde {

#define CHECK_GL_ERROR \
{ \
GLenum error; \
if( (error = glGetError()) != GL_NO_ERROR ){ \
LOG_ERROR("OpenGL Error");\
std::cout << "Line: " << __LINE__ << " error #: " << error << std::endl;\
}\
}
    const GLenum GLFWRenderingDevice::sShaderTypes[] = {
        GL_VERTEX_SHADER,
        GL_FRAGMENT_SHADER,

    };

    const GLenum GLFWRenderingDevice::sPrimitiveTypes[] = {
        GL_TRIANGLES,
        GL_TRIANGLE_STRIP
    };

    /* ****************************
     * Construction & Destruction *
     * ***************************/
    GLFWRenderingDevice::GLFWRenderingDevice() {
    }

    GLFWRenderingDevice::~GLFWRenderingDevice() {
    }

    /* ******************
     * Context Creation *
     * *****************/
    void GLFWRenderingDevice::CreateWindow(const U32 &width, const U32 &height,
                                           const U32 &poxX, const U32 &posY) {
        if(!glfwInit()) {
            throw std::runtime_error("Error creating GLFW Window. Failed glfwInit()");
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_SAMPLES, 32);
        mWindow = glfwCreateWindow(width, height, "Black Dog Engine", NULL, NULL);

        if(!mWindow) {
            glfwTerminate();
            throw std::runtime_error("Error creating GLFW Window. Failed glfwCreateWindow()");
        }

        glfwMakeContextCurrent(mWindow);
    }

    void GLFWRenderingDevice::CreateFullScreen() {
    }

    bool GLFWRenderingDevice::ShouldClose() {
        return glfwWindowShouldClose(mWindow);
    }

    /* ********************
     * Background Methods *
     * *******************/
    void GLFWRenderingDevice::SetBackgroundColor(const ColorRGB &bgColor) {
        glClearColor(bgColor.R(), bgColor.G(), bgColor.B(), 0);
    }

    /* ****************
     * Buffer Methods *
     * ***************/
    void GLFWRenderingDevice::ClearColorBuffer() {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void GLFWRenderingDevice::ClearDepthBuffer() {
        glClear(GL_DEPTH_BUFFER_BIT);
    }

    void GLFWRenderingDevice::ClearStencilBuffer() {
        glClear(GL_STENCIL_BUFFER_BIT);
    }

    void GLFWRenderingDevice::ClearBuffers() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    }

    void GLFWRenderingDevice::SwapBuffers() {
        glfwSwapBuffers(mWindow);
        glfwPollEvents();
    }
    /* ******************
     * Geometry Loading *
     * *****************/
    void            GLFWRenderingDevice::LoadGeometry(GeometryBasePtr geometry) {
        GLuint vao;
        glGenVertexArrays(1, &vao);
        CHECK_GL_ERROR;
        BindingInfoPtr vaoBI = std::make_shared<BindingInfo>(vao);
        BindVertexArray( vaoBI );
        BindingInfoPtr bi = CreateVertexBuffer();
        BindVertexBuffer(bi);
        LoadDataToVertexBuffer(bi, geometry);
        geometry->SetBindingInfo( bi );

        for(int i=0; i<(int)VertexDataSourceSemantics::MAX_VERTEX_DATA_SOURCE_SEMANTICS;
                ++i) {
            auto vds = geometry->GetVertexDataSourceForSemantics( (VertexDataSourceSemantics) i );
            glEnableVertexAttribArray(i);
            CHECK_GL_ERROR;
            GLenum isFloat = (vds->IsFloat() ? GL_FLOAT : GL_INT);
            glVertexAttribPointer(i,
                                  vds->GetComponentCount(),
                                  isFloat,
                                  GL_FALSE,
                                  vds->GetStride(),
                                  (void *)(vds->GetOffset()));
            CHECK_GL_ERROR;
        }

        LoadElementBuffer( geometry->GetElementDataSource() );
        geometry->SetVertexArrayBindingInfo( vaoBI );
    }

    BindingInfoPtr GLFWRenderingDevice::CreateVertexBuffer() {
        GLuint vbo;
        glGenBuffers(1, &vbo);
        CHECK_GL_ERROR;
        BindingInfoPtr bi = std::make_shared<BindingInfo>(vbo);
        return bi;
    }

    void GLFWRenderingDevice::BindVertexBuffer(BindingInfoPtr bi) {
        glBindBuffer(GL_ARRAY_BUFFER, bi->GetBindingID());
        CHECK_GL_ERROR;
        bi->Bind();
    }

    void GLFWRenderingDevice::LoadDataToVertexBuffer(BindingInfoPtr bi,
            GeometryBasePtr geometry) {
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*geometry->GetVertexCount(),
                     geometry->GetVertexBuffer(), GL_STATIC_DRAW);
        CHECK_GL_ERROR;
    }

    void GLFWRenderingDevice::UnbindVertexBuffer(BindingInfoPtr bi) {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        bi->Unbind();
    }

    void GLFWRenderingDevice::DeleteVertexBuffer(BindingInfoPtr bi) {
        GLuint vbo = bi->GetBindingID();
        glDeleteBuffers(1, &vbo);
    }

    void GLFWRenderingDevice::LoadElementBuffer(ElementDataSourcePtr elements) {
        auto bi = CreateVertexBuffer();
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bi->GetBindingID());
        CHECK_GL_ERROR;
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements->GetSizeInBytes(),
                     elements->GetElements(), GL_STATIC_DRAW);
        CHECK_GL_ERROR;
        elements->SetBindingInfo(bi);
        bi->Bind();
    }

    void GLFWRenderingDevice::BindVertexArray(BindingInfoPtr bi) {
        glBindVertexArray( bi->GetBindingID() );
        CHECK_GL_ERROR;
        bi->Bind();
    }

    void GLFWRenderingDevice::DrawElements(ElementDataSourcePtr elements) {
        glDrawElements(sPrimitiveTypes[elements->GetPrimitiveType()], // translate the primitive type
                       elements->GetElementsCount(),
                       GL_UNSIGNED_INT,
                       0);
        CHECK_GL_ERROR;
    }

    /* *********
     * Shaders *
     * ********/
    void GLFWRenderingDevice::LoadShaderProgram(ShaderProgramPtr shaderProgram) {
        GLuint programID = glCreateProgram();

        // Load shaders and attach them to the program
        for(int i=0; i< (int)Shader::ShaderType::MAX_SHADER_TYPES; ++i) {
            auto shader = shaderProgram->GetShader( (Shader::ShaderType)i );

            if(shader != nullptr) {
                LoadShader( shader );
                glAttachShader(programID, shader->GetBindingInfo()->GetBindingID());
                CHECK_GL_ERROR;
            }
        }

        // Bind output colors
        for(int i=0; i< (int)ShaderProgram::ShaderOutputType::MAX_SHADEROUTPUT_TYPE;
                ++i) {
            const char *name = shaderProgram->GetOutputName( (ShaderProgram::ShaderOutputType) i ).c_str();
            glBindFragDataLocation(programID, i, name);
            CHECK_GL_ERROR;
        }

        // Link and Bind the program
        glLinkProgram( programID );
        CHECK_GL_ERROR;
        BindingInfoPtr bi = std::make_shared<BindingInfo>(programID);
        bi->Bind();
        shaderProgram->SetBindingInfo( bi );
        
        // Load the uniforms
        for(int i=0; i<(int)ShaderUniformSemantics::MAX_UNIFORMS; ++i){
            auto uniform = shaderProgram->GetUniformForSemantics((ShaderUniformSemantics)i);
            
            if(!uniform) continue;
            
            loadUniform(shaderProgram, uniform);
        }
        
        // Load the custom uniforms
        auto customUniforms = shaderProgram->CustomUniforms();
        for(auto uniform : customUniforms){
            loadUniform(shaderProgram, uniform);
        }

        // detach and delete the shaders, so that they do not occupy driver memory
        for(int i=0; i<(int)Shader::ShaderType::MAX_SHADER_TYPES; ++i) {
            auto shader = shaderProgram->GetShader((Shader::ShaderType)i);

            if(shader != nullptr) {
                glDetachShader(programID, shader->GetBindingInfo()->GetBindingID());
                glDeleteShader(shader->GetBindingInfo()->GetBindingID());
            }
        }
    }
    
    void GLFWRenderingDevice::loadUniform(ShaderProgramPtr shader, ShaderUniformPtr uniform){
        auto name = uniform->GetNameInShader();
        GLint location = glGetUniformLocation(shader->GetBindingInfo()->GetBindingID(), name.c_str());
        
        if(location < 0){
            LOG(Logger::LoggerLevel::Error, "Uniform not found");
            return;
        }
        
        BindingInfoPtr uniformBI = std::make_shared<BindingInfo>(location);
        uniformBI->Bind();
        uniform->SetBindingInfo(uniformBI);
    }

    void GLFWRenderingDevice::LoadShader(ShaderPtr shader) {
        GLuint shaderId = glCreateShader( sShaderTypes[ (int)
                                          shader->GetShaderType() ] );
        const char *source = shader->GetSource().c_str();
        glShaderSource(shaderId, 1, &source, NULL);
        CHECK_GL_ERROR;
        glCompileShader(shaderId);
        CHECK_GL_ERROR;
        // Check for compile problems
        GLint status;
        glGetShaderiv(shaderId, GL_COMPILE_STATUS, &status);
        CHECK_GL_ERROR;

        if( status != GL_TRUE ) {
            LOG_ERROR("Error compiling shader");
            char buffer[512];
            glGetShaderInfoLog(shaderId, 512, NULL, buffer);
            LOG_ERROR(buffer);
        }

        BindingInfoPtr bi = std::make_shared<BindingInfo>(shaderId);
        shader->SetBindingInfo( bi );
    }

    void GLFWRenderingDevice::SetShaderProgram(ShaderProgramPtr shaderProgram) {
        glUseProgram( shaderProgram->GetBindingInfo()->GetBindingID() );
        shaderProgram->GetBindingInfo()->Bind();
    }
    
    /* ***********
     * Materials *
     * **********/
    void GLFWRenderingDevice::SetMaterial(MaterialPtr material){
        // First, set the shader program
        SetShaderProgram(material->GetShaderProgram());
        
        // then, set all custom uniforms
        auto uniformsIter = material->UniformValuesBegin();
        auto uniformsEndIter = material->UniformValuesEnd();
        for(/**/; uniformsIter != uniformsEndIter; ++uniformsIter){
            uniformsIter->second->Set( shared_from_this() );
        }
    }
    
    /* *****************
     * Uniform Setting *
     * ****************/
    void GLFWRenderingDevice::SetUniformValue(ShaderUniformPtr uniform, const float &f){
        glUniform1f(uniform->GetBindingInfo()->GetBindingID(), f);
    }
    
    void GLFWRenderingDevice::SetUniformValue(ShaderUniformPtr uniform, const Vector2 &v){
        glUniform2f(uniform->GetBindingInfo()->GetBindingID(), v.X(), v.Y());
    }
    
    void GLFWRenderingDevice::SetUniformValue(ShaderUniformPtr uniform, const Vector3 &v){
        glUniform3f(uniform->GetBindingInfo()->GetBindingID(), v.X(), v.Y(), v.Z());
    }
    
    void GLFWRenderingDevice::SetUniformValue(ShaderUniformPtr uniform, const Vector4 &v){
        glUniform4f(uniform->GetBindingInfo()->GetBindingID(), v.X(), v.Y(), v.Z(), v.W());
    }
    
    void GLFWRenderingDevice::SetUniformValue(ShaderUniformPtr uniform, const Quaternion &q){
        glUniform4f(uniform->GetBindingInfo()->GetBindingID(), q.X(), q.Y(), q.Z(), q.W());
    }
    
    void GLFWRenderingDevice::SetUniformValue(ShaderUniformPtr uniform, const ColorRGB &c){
        glUniform3f(uniform->GetBindingInfo()->GetBindingID(), c.R(), c.G(), c.B());
    }
    
    void GLFWRenderingDevice::SetUniformValue(ShaderUniformPtr uniform, const ColorRGBA &c){
        glUniform4f(uniform->GetBindingInfo()->GetBindingID(), c.R(), c.G(), c.B(), c.A());
    }
    
    void GLFWRenderingDevice::SetUniformValue(ShaderUniformPtr uniform, const Matrix3 &m){
        glUniformMatrix3fv(uniform->GetBindingInfo()->GetBindingID(), 1, GL_FALSE, (const GLfloat*)&m);
    }
    
    void GLFWRenderingDevice::SetUniformValue(ShaderUniformPtr uniform, const Matrix4 &m){
        glUniformMatrix4fv(uniform->GetBindingInfo()->GetBindingID(), 1, GL_FALSE, (const GLfloat*)&m);
    }
} // GLFWRenderingDevice::namespace bde
