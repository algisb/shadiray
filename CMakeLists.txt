cmake_minimum_required (VERSION 3.1.0)

project (shadiray-demo)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "./bin")
SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "./bin")
SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "./bin")
#glew------------------------------------------------------
#include_directories ("./external/glew/include")
add_subdirectory("./external/glew/build/cmake")
include_directories ("./external/glew/include")
add_definitions(-DGLEW_STATIC)



#opengl----------------------------------------------------
find_package(OpenGL)
include_directories( ${OPENGL_INCLUDE_DIRS} )


#glfw------------------------------------------------------
set(BUILD_SHARED_LIBS OFF CACHE BOOL "")
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "")
set(GLFW_BUILD_DOCS OFF CACHE BOOL "")
set(GLFW_INSTALL OFF CACHE BOOL "")

include_directories ("./external/glfw/include")
add_subdirectory("./external/glfw")
add_definitions(-DGLFW_STATIC)

#tinyobjloader-------------------------------------------------------
include_directories ("./external/tinyobjloader")

#kelp engine-----------------------------------------------
include_directories ("./src")
file(GLOB KELP_SRC "./src/*.cpp" "./src/component/*.cpp" "./src/kep/*.cpp" "./src/world/*.cpp" "./src/shadiray/*cpp")
add_executable(shadiray-demo ${KELP_SRC})
target_link_libraries (shadiray-demo ${OPENGL_LIBRARIES} glfw glew_s )
