
add_subdirectory(MathLib)

file(GLOB srcs
    "*.h"
    "*.cpp"
)

add_library(blackdogengine ${srcs})
target_link_libraries(blackdogengine bdemath)
