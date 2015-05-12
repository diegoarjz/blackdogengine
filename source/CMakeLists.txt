
add_subdirectory(Debug)
add_subdirectory(MathLib)
add_subdirectory(Geometry)

file(GLOB srcs
    "*.h"
    "*.cpp"
)

add_library(blackdogengine ${srcs})
target_link_libraries(blackdogengine bdemath)
target_link_libraries(blackdogengine geometry)
target_link_libraries(blackdogengine bdedebug)
