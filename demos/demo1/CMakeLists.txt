
add_executable(demo1 main.cpp)
target_link_libraries(demo1 blackdogengine)
target_link_libraries(demo1 glfwrenderer)
target_link_libraries(demo1 ${OpenGL_LIBRARY})
target_link_libraries(demo1 ${COCOA_LIBRARY})
target_link_libraries(demo1 ${CoreVideo_LIBRARY})
target_link_libraries(demo1 ${IOKit_LIBRARY})
target_link_libraries(demo1 glfw3)
