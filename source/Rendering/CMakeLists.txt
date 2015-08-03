add_subdirectory(GLFW)

file(GLOB srcs
    "*.h"
    "*.cpp"
)

add_library(rendering ${srcs})
target_link_libraries(rendering bdeSystem)

file(GLOB headers
    "*.h"
)
INSTALL(FILES ${headers} DESTINATION include/blackdogengine/rendering)

INSTALL(TARGETS rendering ARCHIVE DESTINATION lib/blackdogengine/rendering)
