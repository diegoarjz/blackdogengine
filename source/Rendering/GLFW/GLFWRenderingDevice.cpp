#include "GLFWRenderingDevice.h"


namespace bde{
        /* ****************************
         * Construction & Destruction *
         * ***************************/
        GLFWRenderingDevice::GLFWRenderingDevice(){

        }
        
        GLFWRenderingDevice::~GLFWRenderingDevice(){

        }

        /* ******************
         * Context Creation *
         * *****************/
        void GLFWRenderingDevice::CreateWindow(const U32 &width, const U32 &height, const U32 &poxX, const U32 &posY){
            if(!glfwInit()){
                throw std::runtime_error("Error creating GLFW Window. Failed glfwInit()");
            }

            mWindow = glfwCreateWindow(width, height, "Black Dog Engine", NULL, NULL);

            if(!mWindow){
                glfwTerminate();
                throw std::runtime_error("Error creating GLFW Window. Failed glfwCreateWindow()");
            }

            glfwMakeContextCurrent(mWindow);
        }

        void GLFWRenderingDevice::CreateFullScreen(){

        }

        bool GLFWRenderingDevice::ShouldClose(){
            return glfwWindowShouldClose(mWindow);
        }

        /* ********************
         * Background Methods *
         * *******************/
        void GLFWRenderingDevice::SetBackgroundColor(const ColorRGB &bgColor){
            glClearColor(bgColor.R(), bgColor.G(), bgColor.B(), 0);
        }

        /* ****************
         * Buffer Methods *
         * ***************/
        void GLFWRenderingDevice::ClearColorBuffer(){
            glClear(GL_COLOR_BUFFER_BIT);
        }

        void GLFWRenderingDevice::ClearDepthBuffer(){

            glClear(GL_DEPTH_BUFFER_BIT);
        }

        void GLFWRenderingDevice::ClearStencilBuffer(){
            glClear(GL_STENCIL_BUFFER_BIT);
        }

        void GLFWRenderingDevice::ClearBuffers(){
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        }

        void GLFWRenderingDevice::SwapBuffers(){
            glfwSwapBuffers(mWindow);
            glfwPollEvents();
        }
} // namespace bde
