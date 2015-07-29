
file(GLOB srcs
    "*.h"
    "*.cpp"
)

add_library(geometry ${srcs})

INSTALL(TARGETS geometry ARCHIVE DESTINATION lib/blackdogengine/geometry)
