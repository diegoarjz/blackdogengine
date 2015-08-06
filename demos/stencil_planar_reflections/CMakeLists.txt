
add_executable(stencilReflections main.cpp)
target_link_libraries(stencilReflections glfw3)
target_link_libraries(stencilReflections blackdogengine)
target_link_libraries(stencilReflections glfwrenderer)
target_link_libraries(stencilReflections ${EXTRA_LIBRARIES} )
target_link_libraries(stencilReflections -lpthread)

FILE(COPY shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
