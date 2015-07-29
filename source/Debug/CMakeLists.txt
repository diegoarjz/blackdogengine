file(GLOB srcs
    "*.h"
    "*.cpp"
)

add_library(bdedebug ${srcs})

INSTALL(TARGETS bdedebug ARCHIVE DESTINATION lib/blackdogengine/debug)
