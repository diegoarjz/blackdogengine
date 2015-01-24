cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

# GLM Include DIR
set(GLM_Include_Dir "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glm")
include_directories(AFTER SYSTEM ${GLM_Include_Dir})

# Set c++11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

project("BlackDogEngine")

add_subdirectory(source)


