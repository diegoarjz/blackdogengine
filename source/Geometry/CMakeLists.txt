
file(GLOB srcs
    "*.h"
    "*.cpp"
)

add_library(geometry ${srcs})

file(GLOB headers
    "*.h"
)
INSTALL(FILES ${headers} DESTINATION include/blackdogengine/geometry)

INSTALL(TARGETS geometry ARCHIVE DESTINATION lib/blackdogengine/geometry)
