file(GLOB srcs
    "*.h"
    "*.cpp"
)

add_library(meta ${srcs})

file(GLOB headers
    "*.h"
)
INSTALL(FILES ${headers} DESTINATION include/blackdogengine/meta)

INSTALL(TARGETS meta ARCHIVE DESTINATION lib/blackdogengine/meta/)
