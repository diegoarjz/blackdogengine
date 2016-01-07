
FILE(GLOB srcs RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

FOREACH(source ${srcs})

    string( REPLACE ".cpp" "" testname ${source} )

    add_executable(${testname} ${source})
    target_link_libraries(${testname} bdemath)
    target_link_libraries(${testname} boost_unit_test_framework-mt)
    add_test(NAME ${testname} COMMAND ${testname})
ENDFOREACH(source ${srcs})
