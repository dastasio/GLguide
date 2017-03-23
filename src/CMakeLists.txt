link_directories( ${PROJECT_SOURCE_DIR}/win/glew/lib)
link_directories( ${PROJECT_SOURCE_DIR}/win/SDL2/lib)

add_library( my_lib STATIC global.h dav_sdl.h textures.h ShaderMan.hpp WindowMan.hpp
	dav_sdl.cpp textures.cpp ShaderMan.cpp WindowMan.cpp
	shader.frag shader.vert) 

target_link_libraries( my_lib ${OPENGL_LIBRARIES} glm_static assimp)
include_directories( ${OPENGL_INCLUDE_DIR} ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/glfw/include
	${PROJECT_SOURCE_DIR}/assimp/include)

# setting c++ version
target_compile_features( my_lib PRIVATE cxx_raw_string_literals)

if( SYSUNIX)
	target_link_libraries( my_lib ${GLEW_LIBRARY} ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY})
	include_directories( ${GLEW_INCLUDE_DIR} ${SDL2_INCLUDE_DIR})
elseif( SYSWINDOWS)
	target_link_libraries( my_lib glew32s opengl32 SDL2 SDL2_image)
	include_directories( ${PROJECT_SOURCE_DIR}/win/glew/include ${PROJECT_SOURCE_DIR}/win/SDL2/include)
endif()