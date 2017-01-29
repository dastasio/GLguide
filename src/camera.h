#pragma once
#include "global.h"

class Camera {
public:
	Camera();
	~Camera();

	GLvoid move(GLboolean hor, GLfloat speed);
	GLvoid turn(GLboolean vertical, GLfloat angle);
	
	GLvoid pointCamera( glm::vec3 p, glm::vec3 target, glm::vec3 up);

	glm::mat4 getMatrix() { return camSpace; }
	glm::vec3 getPosition() { return pos; }
private:

	glm::vec3 pos;
	glm::vec3 U, V, N;

	glm::mat4 camSpace;
 };