#pragma once
#include "global.h"

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
	GLint locViewPos, locModel, locView, locProj, locLightCol, locObjCol;
	GLint ligModel, ligView, ligProj, ligPos;
	GLint matDiffLoc, matSpecLoc, matShineLoc;
	GLint lightDirLoc, lightAmbLoc, lightDiffLoc, lightSpecLoc;

	// OpenGL buffers
	GLuint VAO, VBO, EBO, lightVAO, gProgram, lightProgram, diffuseTexture, specTexture;

	// window settings
	const GLfloat width = 1024, height = 720;


	glm::vec3 lightPos = glm::vec3(1.2, 1.0, 2.0);
	SDL_Window* thisWindow;
	SDL_GLContext thisContext;
	
	
	glm::vec3 cubePositions[10] = {
		glm::vec3( 0.0f,  0.0f,  0.0f),
		glm::vec3( 2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3( 2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3( 1.3f, -2.0f, -2.5f),
		glm::vec3( 1.5f,  2.0f, -2.5f),
		glm::vec3( 1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};
};
