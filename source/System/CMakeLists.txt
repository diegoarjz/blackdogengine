# set the threading wrapper to use pthread library
add_definitions(-DUSE_PTHREAD=0)

file(GLOB srcs
    "*.h"
    "*.cpp"
)

add_library(bdeSystem ${srcs})

file(GLOB headers
    "*.h"
)
INSTALL(FILES ${headers} DESTINATION include/blackdogengine/System)

INSTALL(TARGETS bdeSystem ARCHIVE DESTINATION lib/blackdogengine/System)
