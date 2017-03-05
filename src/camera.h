#pragma once
#include "global.h"

enum camEnum {
	CAM_MOVE_UP,
	CAM_MOVE_RIGHT,
	CAM_MOVE_FORWARD,
	CAM_ROT_PITCH,
	CAM_ROT_YAW
};

class Camera {
public:
	Camera( glm::vec3 position, GLboolean perspective = GL_TRUE,
		   GLfloat nearPlane = 0.1, GLfloat farPlane = 100, GLfloat ar = 1.42,
		   GLfloat fov = glm::radians(45.0), GLfloat height_res = 720.f);
	~Camera();

	GLvoid move(camEnum dir, GLfloat speed);
	GLvoid turn(camEnum dir, GLfloat angle);
	
	GLvoid pointCamera( glm::vec3 p, glm::vec3 target, glm::vec3 up);

	glm::mat4 getMatrix() { return projection * camSpace; }
	glm::vec3 getPosition() { return pos; }
	glm::vec3 getTarget() { return N; }
private:

	glm::vec3 pos;
	glm::vec3 U, V, N;

	glm::mat4 camSpace, projection;
	GLboolean isPerspective;
 };
