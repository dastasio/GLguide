#pragma once
#include "global.h"

class Camera {
public:
	Camera();
	~Camera();

	GLvoid move( glm::vec3 m);
	GLvoid turn(GLboolean vertical, GLfloat angle);
	
	GLvoid pointCamera( glm::vec3 target, glm::vec3 up);

	glm::mat4 getMatrix() { return camSpace; };
private:

	glm::vec3 pos;
	glm::vec3 U, V, N;

	glm::mat4 camSpace;
 };