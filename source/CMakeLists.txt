add_subdirectory(System)
add_subdirectory(Meta)
add_subdirectory(Debug)
add_subdirectory(MathLib)
add_subdirectory(Geometry)
add_subdirectory(Rendering)

file(GLOB srcs
    "*.h"
    "*.cpp"
)

add_library(blackdogengine ${srcs})
target_link_libraries(blackdogengine bdemath)
target_link_libraries(blackdogengine meta)
target_link_libraries(blackdogengine geometry)
target_link_libraries(blackdogengine bdeSystem)
target_link_libraries(blackdogengine bdedebug)
target_link_libraries(blackdogengine rendering)
