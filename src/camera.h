#pragma once
#include "global.h"

enum camEnum {
	CAM_MOVE_UP,
	CAM_MOVE_RIGHT,
	CAM_MOVE_FORWARD
};

class Camera {
public:
	Camera();
	~Camera();

	GLvoid move(camEnum dir, GLfloat speed);
	GLvoid turn(GLboolean vertical, GLfloat angle);
	
	GLvoid pointCamera( glm::vec3 p, glm::vec3 target, glm::vec3 up);

	glm::mat4 getMatrix() { return camSpace; }
	glm::vec3 getPosition() { return pos; }
private:

	glm::vec3 pos;
	glm::vec3 U, V, N;

	glm::mat4 camSpace;
 };