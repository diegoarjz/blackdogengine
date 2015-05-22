# set the threading wrapper to use pthread library
add_definitions(-DUSE_PTHREAD=0)

file(GLOB srcs
    "*.h"
    "*.cpp"
)

add_library(system ${srcs})
