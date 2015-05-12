
file(GLOB srcs
    "*.h"
    "*.cpp"
)

add_library(bdemath ${srcs})
target_link_libraries(bdemath CGAL)
