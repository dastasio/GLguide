#include "textures.h"

GLuint loadTexture(const GLchar* path) {
	// loading texture file
	SDL_Surface* image = IMG_Load(path);
	if (image == nullptr) {
		std::cerr << "LOADING ERROR: Could not load " << path << std::endl << IMG_GetError() << std::endl;
		exit(EXIT_FAILURE);
	}

	// generating texture
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
	glGenerateMipmap(GL_TEXTURE_2D);
	

	// freeing memory
	SDL_FreeSurface(image);
	glBindTexture(GL_TEXTURE_2D, 0);
	
	return texture;
}
