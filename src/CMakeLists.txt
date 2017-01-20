link_directories( ${PROJECT_SOURCE_DIR}/win/glew/lib)
link_directories( ${PROJECT_SOURCE_DIR}/win/SDL2/lib)

add_library( my_lib STATIC global.h common.h common.cpp glfw_wind.h glfw_wind.cpp cube.h
	textures.cpp textures.h cube.cpp dav_sdl.cpp dav_sdl.h shader.vert shader.frag) 

target_link_libraries( my_lib ${OPENGL_LIBRARIES} glm_static SDL2)
include_directories( ${OPENGL_INCLUDE_DIR} ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/glfw/include)

# setting c++ version
target_compile_features( my_lib PRIVATE cxx_raw_string_literals)

if( SYSUNIX)
	target_link_libraries( my_lib ${GLEW_LIBRARIES} ${SDL_LIBRARIES})
	include_directories( ${GLEW_INCLUDE_DIR} ${SDL_INCLUDE_DIRS})
elseif( SYSWINDOWS)
	target_link_libraries( my_lib glew32s opengl32 SDL2 SDL2_image)
	include_directories( ${PROJECT_SOURCE_DIR}/win/glew/include ${PROJECT_SOURCE_DIR}/win/SDL2/include)
endif()