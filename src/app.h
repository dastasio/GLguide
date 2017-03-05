#pragma once
#include "global.h"
#include "dav_model.hpp"
#include "camera.h"

class App {
public:
	
	App(GLint window_width = 1024, GLint window_height = 720);
	~App();

	// init functions
	GLvoid initWindow();

	GLvoid initBuffers();
	GLvoid initMatrices();
	GLvoid render();
	GLvoid loop();
	GLboolean grabInput();
private:
	Camera* cam;
	
	// window data
	GLfloat main_width, main_height;
	SDL_Window* main_window;
	SDL_GLContext main_context;
	
	// OpenGL data
	GLuint program;
	
	
	// assimp utilities
	Assimp::Importer importer;
	
	
	davModel* suit;
	
	glm::mat4 model, view;
	GLuint locModel, locView;
};











