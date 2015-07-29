file(GLOB srcs
    "*.h"
    "*.cpp"
)

add_library(meta ${srcs})

INSTALL(TARGETS meta ARCHIVE DESTINATION lib/blackdogengine/meta/)
