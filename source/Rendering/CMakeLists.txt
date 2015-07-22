add_subdirectory(GLFW)

file(GLOB srcs
    "*.h"
    "*.cpp"
)

add_library(rendering ${srcs})
target_link_libraries(rendering bdeSystem)
