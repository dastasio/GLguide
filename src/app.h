#pragma once
#include "global.h"
#include "dav_model.h"
#include "dav_sdl.h"
#include "camera.h"
#include "objs.h"

class App {
public:
	
	App();
	~App();

	// init functions
	GLvoid initWindow();
	GLvoid initProjection(GLfloat fov = glm::radians(45.0f), GLfloat ar = 1.42f);
	GLvoid initBuffers();
	GLvoid initMatrices();
	GLvoid initCube();

	GLboolean grabInput();
	GLvoid loop();
private:
	GLvoid render();

	std::vector<GLfloat> models;

	std::vector<GLuint> indices;

	// matrices
	glm::mat4 model, view, projection;
	GLint locViewPos, locModel, locView, locProj;
	GLint ligModel, ligView, ligProj, ligPos;
	GLint matDiffLoc, matSpecLoc, matShineLoc;
	
	GLint dirDirLoc, dirAmbLoc, dirDiffLoc, dirSpecLoc;
	GLint	pntPosLoc[4],
			pntConstLoc[4],
			pntLinLoc[4],
			pntQuadLoc[4],
			pntAmbLoc[4],
			pntDiffLoc[4],
			pntSpecLoc[4];

	// OpenGL buffers
	GLuint VAO, VBO, EBO, lightVAO, gProgram, lightProgram;

	// window settings
	const GLfloat width = 1024, height = 720;


	glm::vec3 lightPos = glm::vec3(1.2, 1.0, 2.0);
	SDL_Window* thisWindow;
	SDL_GLContext thisContext;
	
	
	Model* nanosuit;
};











