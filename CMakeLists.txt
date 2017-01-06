cmake_minimum_required( VERSION 3.1)

project( GLguide)
set( EXEC_NAME "DoubleTr")

set( EXECUTABLE_OUTPUT_PATH "${PROJECT_BINARY_DIR}/bin")
set( LIBRARY_OUTPUT_PATH ${EXECUTABLE_OUTPUT_PATH})
set( SOURCE_LIB "${PROJECT_SOURCE_DIR}/src")
set( CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmodules")

message( "system name: " ${CMAKE_SYSTEM})
message( "system processor: " ${CMAKE_SYSTEM_PROCESSOR})


if( ${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	set( SYSWINDOWS 1)
	message( "detected Windows system")
	link_directories( ${PROJECT_SOURCE_DIR}/win/glew/lib)
else()
	set( SYSUNIX 1)
	message( "detected Unix system")
endif()
find_package( OpenGL REQUIRED)

# building GLFW variables
set( GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set( GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
SET( GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
# building glm variables
set( GLM_STATIC_LIBRARY_ENABLE ON CACHE BOOL "" FORCE)

add_executable( ${EXEC_NAME} "main.cpp")
add_subdirectory( ${SOURCE_LIB}) # adding my library
add_subdirectory( ${PROJECT_SOURCE_DIR}/glfw) # adding glfw library
add_subdirectory( ${PROJECT_SOURCE_DIR}/glm) # adding glm library

# setting c++ version
target_compile_features( ${EXEC_NAME} PRIVATE cxx_nullptr)

target_link_libraries( ${EXEC_NAME} my_lib ${OPENGL_LIBRARIES} glfw glm_static)
include_directories( ${SOURCE_LIB} ${PROJECT_SOURCE_DIR} ${OPENGL_INCLUDE_DIR} ${PROJECT_SOURCE_DIR}/glfw/include)

if( SYSUNIX)
	find_package( GLEW REQUIRED)
	target_link_libraries( ${EXEC_NAME} ${GLEW_LIBRARIES})
	include_directories( ${GLEW_INCLUDE_DIR})
elseif( SYSWINDOWS)
	target_link_libraries( ${EXEC_NAME} glew32s opengl32)
	include_directories( ${PROJECT_SOURCE_DIR}/win/glew/include)
endif()