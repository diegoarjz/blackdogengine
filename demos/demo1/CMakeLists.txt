
add_executable(demo1 main.cpp)
target_link_libraries(demo1 glfw3)
target_link_libraries(demo1 blackdogengine)
target_link_libraries(demo1 glfwrenderer)
target_link_libraries(demo1 ${EXTRA_LIBRARIES} )
target_link_libraries(demo1 -lpthread)

FILE(COPY shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
