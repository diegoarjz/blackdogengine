cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)

project("BlackDogEngine")

set(BDE_INCLUDES "/usr/local/include/")
include_directories(AFTER SYSTEM ${BDE_INCLUDES})

LINK_DIRECTORIES("/usr/local/lib/")

IF(APPLE)
    INCLUDE_DIRECTORIES ( /System/Library/Frameworks )

    FIND_LIBRARY(COCOA_LIBRARY Cocoa)
    FIND_LIBRARY(OpenGL_LIBRARY OpenGL )
    FIND_LIBRARY(IOKit_LIBRARY IOKit)
    FIND_LIBRARY(CoreVideo_LIBRARY CoreVideo)
    FIND_LIBRARY(GLFW3 glfw3)
    MARK_AS_ADVANCED (COCOA_LIBRARY
                      IOKit_LIBRARY
                      CoreVideo_LIBRARY
                      OpenGL_LIBRARY)

    SET( EXTRA_LIBRARIES ${GLFW3} ${COCOA_LIBRARY} ${OpenGL_LIBRARY} ${IOKit_LIBRARY} ${CoreVideo_LIBRARY}
                      ${GLFW_LIBRARIES})
ELSEIF(UNIX)
    FIND_PACKAGE(PkgConfig REQUIRED)
    pkg_search_module(GLFW REQUIRED glfw3)
    include_directories(${GLFW_INCLUDE_DIRS})

    find_package(GLEW REQUIRED)
    if (GLEW_FOUND)
        include_directories(${GLEW_INCLUDE_DIRS})
        link_libraries(${GLEW_LIBRARIES})
    endif()

    #SET( EXTRA_LIBRARIES GLFW_LIBRARIES OpenGL_LIBRARY X11_LIBRARY XXF86VM_LIBRARY XRANDR_LIBRARY XI_LIBRARY )
    SET( EXTRA_LIBRARIES ${GLFW_STATIC_LIBRARIES} ${GLEW_LIBRARIES} )
ENDIF (APPLE)


# Set c++11
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_STANDARD 11)

# Enable testing for the Black Dog Engine Project
enable_testing()

add_subdirectory(source)
add_subdirectory(tests)
add_subdirectory(demos)

add_test(NAME BlackDogEngine    COMMAND UnitTest BlackDogEngine)
add_test(NAME Geometry          COMMAND UnitTest Geometry)
add_test(NAME Thread            COMMAND UnitTest Thread)
add_test(NAME MetaVariable      COMMAND UnitTest MetaVariable)
add_test(NAME MetaFunction      COMMAND UnitTest MetaFunction)
