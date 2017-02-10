link_directories( ${PROJECT_SOURCE_DIR}/win/glew/lib)
link_directories( ${PROJECT_SOURCE_DIR}/win/SDL2/lib)

add_library( my_lib STATIC global.h common.h common.cpp glfw_wind.h glfw_wind.cpp app.h
	textures.cpp textures.h app.cpp dav_sdl.cpp dav_sdl.h camera.h camera.cpp
	objs.h objs.cpp structs.h dav_mesh.h dav_mesh.cpp dav_model.h dav_model.cpp
	light.vert light.frag shader.vert shader.frag) 

target_link_libraries( my_lib ${OPENGL_LIBRARIES} glm_static assimp)
include_directories( ${OPENGL_INCLUDE_DIR} ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/glfw/include
	${PROJECT_SOURCE_DIR}/assimp/include)

# setting c++ version
target_compile_features( my_lib PRIVATE cxx_raw_string_literals)

if( SYSUNIX)
	target_link_libraries( my_lib ${GLEW_LIBRARY} ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY})
	include_directories( ${GLEW_INCLUDE_DIR} ${SDL_INCLUDE_DIRS})
	message("~~~~~~~~~~~~~~~" ${SDL2_LIBRARY})
elseif( SYSWINDOWS)
	target_link_libraries( my_lib glew32s opengl32 SDL2 SDL2_image)
	include_directories( ${PROJECT_SOURCE_DIR}/win/glew/include ${PROJECT_SOURCE_DIR}/win/SDL2/include)
endif()