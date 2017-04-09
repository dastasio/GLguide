link_directories( ${PROJECT_SOURCE_DIR}/win/glew/lib)
link_directories( ${PROJECT_SOURCE_DIR}/win/SDL2/lib)

add_library( denAssets STATIC 
	 den_Mesh.cpp den_Model.cpp textures.cpp
	 den_Mesh.hpp den_Model.hpp textures.h global.h)

target_link_libraries( denAssets denShaders ${OPENGL_LIBRARIES} glm_static assimp)
include_directories(
	${OPENGL_INCLUDE_DIR} 
	${PROJECT_SOURCE_DIR}
	${PROJECT_SOURCE_DIR}/assimp/include)

# setting c++ version
target_compile_features( denAssets PRIVATE cxx_raw_string_literals)

if( SYSUNIX)
	target_link_libraries( denAssets ${GLEW_LIBRARY} ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY})
	include_directories( ${GLEW_INCLUDE_DIR} ${SDL2_INCLUDE_DIR})
elseif( SYSWINDOWS)
	target_link_libraries( denAssets glew32s opengl32 SDL2 SDL2_image)
	include_directories( ${PROJECT_SOURCE_DIR}/win/glew/include ${PROJECT_SOURCE_DIR}/win/SDL2/include)
endif()