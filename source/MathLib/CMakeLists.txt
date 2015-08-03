
file(GLOB srcs
    "*.h"
    "*.cpp"
)

add_library(bdemath ${srcs})
target_link_libraries(bdemath CGAL)

file(GLOB headers
    "*.h"
)
INSTALL(FILES ${headers} DESTINATION include/blackdogengine/mathlib)

INSTALL(TARGETS bdemath ARCHIVE DESTINATION lib/blackdogengine/mathlib)
