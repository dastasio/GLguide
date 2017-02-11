cmake_minimum_required( VERSION 3.1)

project( GLguide)
set( EXEC_NAME "Cube")

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
	link_directories( ${PROJECT_SOURCE_DIR}/win/SDL2/lib)
else()
	set( SYSUNIX 1)
	message( "detected Unix system")
endif()
find_package( OPENGL REQUIRED)
message("" ${OPENGL_INCLUDE_DIR})

# building glm variables
set( GLM_STATIC_LIBRARY_ENABLE ON CACHE BOOL "" FORCE)
set( ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set( BUILD_ASSIMP_SAMPLES OFF CACHE BOOL "" FORCE)

add_executable( ${EXEC_NAME} "main.cpp")
add_subdirectory( ${SOURCE_LIB}) # adding my library
add_subdirectory( ${PROJECT_SOURCE_DIR}/glm) # adding glm library
add_subdirectory( ${PROJECT_SOURCE_DIR}/assimp) # assimp library


# setting c++ version
target_compile_features( ${EXEC_NAME} PRIVATE cxx_nullptr)

target_link_libraries( ${EXEC_NAME} my_lib ${OPENGL_LIBRARIES} glm_static assimp)
include_directories( ${SOURCE_LIB} ${PROJECT_SOURCE_DIR} ${OPENGL_INCLUDE_DIR} ${PROJECT_SOURCE_DIR}/glfw/include 
	${PROJECT_SOURCE_DIR}/assimp/include/)

if( SYSUNIX)
	find_package( GLEW REQUIRED)
	find_package( SDL2 REQUIRED)
	find_package( SDL2_image REQUIRED)
	target_link_libraries( ${EXEC_NAME} ${GLEW_LIBRARY} ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY})
	include_directories( ${GLEW_INCLUDE_DIR} ${SDL2_INCLUDE_DIRS})
elseif( SYSWINDOWS)
	target_link_libraries( ${EXEC_NAME} glew32s opengl32 SDL2 SDL2_image)
	include_directories( ${PROJECT_SOURCE_DIR}/win/glew/include)
	include_directories( ${PROJECT_SOURCE_DIR}/win/SDL2/include)
endif()