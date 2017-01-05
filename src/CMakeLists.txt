link_directories( ${PROJECT_SOURCE_DIR}/win/glew/lib)
add_library( my_lib STATIC global.h common.h common.cpp glfw_wind.h glfw_wind.cpp triangle.h
	triangle.cpp shader.vert shader.frag) 
target_link_libraries( my_lib ${OPENGL_LIBRARIES} glfw glm_static)
include_directories( ${OPENGL_INCLUDE_DIR} ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/glfw/include)

# setting c++ version
target_compile_features( my_lib PRIVATE cxx_raw_string_literals)

if( SYSUNIX)
	target_link_libraries( my_lib ${GLEW_LIBRARIES})
	include_directories( ${GLEW_INCLUDE_DIR})
elseif( SYSWINDOWS)
	target_link_libraries( my_lib glew32s opengl32)
	include_directories( ${PROJECT_SOURCE_DIR}/win/glew/include)
endif()