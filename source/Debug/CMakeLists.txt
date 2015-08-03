file(GLOB srcs
    "*.h"
    "*.cpp"
)

add_library(bdedebug ${srcs})

file(GLOB headers
    "*.h"
)
INSTALL(FILES ${headers} DESTINATION include/blackdogengine/debug)

INSTALL(TARGETS bdedebug ARCHIVE DESTINATION lib/blackdogengine/debug)
