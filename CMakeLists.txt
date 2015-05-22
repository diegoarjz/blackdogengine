cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)

project("BlackDogEngine")

set(BDE_INCLUDES "/usr/local/include/")
include_directories(AFTER SYSTEM ${BDE_INCLUDES})

LINK_DIRECTORIES("/usr/local/lib/")

IF(APPLE)
    INCLUDE_DIRECTORIES ( /System/Library/Frameworks )
    #LINK_DIRECTORIES( /System/Library/Frameworks/OpenGL.framework/Libraries )
    #LINK_DIRECTORIES( /System/Library/Frameworks/Cocoa.framework/Versions/Current )
    FIND_LIBRARY(COCOA_LIBRARY Cocoa)
    FIND_LIBRARY(OpenGL_LIBRARY OpenGL )
    FIND_LIBRARY(IOKit_LIBRARY IOKit)
    FIND_LIBRARY(CoreVideo_LIBRARY CoreVideo)
    MARK_AS_ADVANCED (COCOA_LIBRARY
                      IOKit_LIBRARY
                      CoreVideo_LIBRARY
                      OpenGL_LIBRARY)

    MESSAGE(STATUS "Extra Libs: " ${EXTRA_LIBS})
    MESSAGE(STATUS "Cocoa: " ${COCOA_LIBRARY})
    MESSAGE(STATUS "OpenGL: " ${OpenGL_LIBRARY})
    MESSAGE(STATUS "IOKit: " ${IOKit_LIBRARY})
    MESSAGE(STATUS "CoreVideo: " ${CoreVideo_LIBRARY})
ENDIF (APPLE)


# Set c++11
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_STANDARD 11)

# Enable testing for the Black Dog Engine Project
enable_testing()

add_subdirectory(source)
add_subdirectory(tests)
add_subdirectory(demos)

set_property(TARGET blackdogengine PROPERTY CXX_STANDARD 11)
set_property(TARGET bdemath PROPERTY CXX_STANDARD 11)

add_test(NAME BlackDogEngine    COMMAND UnitTest BlackDogEngine)
add_test(NAME Geometry          COMMAND UnitTest Geometry)
add_test(NAME Thread            COMMAND UnitTest Thread)
