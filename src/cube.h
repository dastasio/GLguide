#pragma once
#include "global.h"

class App {
public:
	
	App();
	~App();

	// init functions
	GLvoid initWindow();
	GLvoid initCube();
	GLvoid initBuffers();
	GLvoid initMatrices();
	GLvoid initTexture();

	GLvoid loop();
private:
	GLvoid render();

	std::vector<GLfloat> cube;
	GLint* indices;

	// matrices
	glm::mat4 model, view, projection;
	GLint locModel, locView, locProj;
	// OpenGL buffers
	GLuint VAO, BO[2], gProgram;

	// window settings
	const GLint width = 1024, height = 720;

	GLuint texSmile, texCont;

	SDL_Window* thisWindow;
	SDL_GLContext thisContext;
};