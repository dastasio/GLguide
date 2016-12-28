cmake_minimum_required( VERSION 3.0)

project( GLguide)

set( EXEC_NAME "version")
set( SOURCE_LIB "${PROJECT_SOURCE_DIR}/src")
set( CMAKE_BINARY_DIR "${PROJECT_SOURCE_DIR}/bin")
set( CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmodules")

find_package( GLFW REQUIRED)
find_package( GLEW REQUIRED)
find_package( OpenGL REQUIRED)

add_subdirectory( ${SOURCE_LIB})

add_executable( ${EXEC_NAME} "main.cpp")
target_link_libraries( ${EXEC_NAME} my_lib ${OPENGL_LIBRARIES} ${GLFW_LIBRARIES} ${GLEW_LIBRARIES})
include_directories( ${EXEC_NAME} ${SOURCE_LIB} ${OPENGL_INCLUDE_DIR} ${GLFW_INCLUDE_DIR} ${GLFW_INCLUDE_DIR})
