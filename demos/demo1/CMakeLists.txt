
add_executable(demo1 main.cpp)
target_link_libraries(demo1 blackdogengine)
target_link_libraries(demo1 glfwrenderer)
target_link_libraries(demo1 ${EXTRA_LIBRARIES} )
target_link_libraries(demo1 -lpthread)

#INSTALL(FILES shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
FILE(COPY shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
