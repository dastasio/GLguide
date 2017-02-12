#pragma once
#include "global.h"
#include "dav_model.hpp"
#include "camera.h"

class App {
public:
	
	App();
	~App();

	// init functions
	GLvoid initWindow();
	GLvoid initProjection(GLfloat fov = glm::radians(45.0f), GLfloat ar = 1.42f);

	GLvoid initBuffers();
	GLvoid initMatrices();
	GLvoid render();
	GLvoid loop();
	GLboolean grabInput();
private:
	Camera* cam;
	
	// window data
	const GLint main_width = 1024, main_height = 720;
	SDL_Window* main_window;
	SDL_GLContext main_context;
	
	// OpenGL data
	GLuint program;
	
	
	// assimp utilities
	Assimp::Importer importer;
	
	
	davModel* suit;
	
	glm::mat4 projection, model, view;
	GLuint locProj, locModel, locView;
};











