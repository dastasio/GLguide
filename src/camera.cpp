#include "camera.h"

using namespace glm;

Camera::Camera() {
	camSpace = mat4(1.0);
	pos = vec3(0.0, 0.0, 3.0);

	pointCamera(pos,vec3(0.0, 0.0,-1.0), vec3( 0.0, 1.0, 0.0));
}

Camera::~Camera() {
	delete &pos;
	delete &U;
	delete &V;
	delete &N;
	delete &camSpace;
}


/* move( vec3);
 - parameters: vec3 Cameraect representing wanted motion on x, y, z axis
 - returns: VOID
 - s.e.: updates private 'pos' vector with camera new position
*/
GLvoid Camera::move( camEnum dir, GLfloat speed) {
	switch (dir) {
	case CAM_MOVE_RIGHT:
		pos += normalize(cross(N, U)) * speed;
		break;

	case CAM_MOVE_FORWARD:
		pos += N * speed;
		break;

	case CAM_MOVE_UP:
		pos += U * speed;
		break;
	default:
		break;
	}

	pointCamera( pos, N, U);
}


/* turn( GLboolean, GLfloat);
 - parameters: bool indicating direction of rotation; angle of rotation
 - returns: VOID
 - s.e.: calls pointCamera
*/
GLvoid Camera::turn(camEnum dir, GLfloat angle) {
	GLfloat c = cosf(angle), s = sinf(angle);
	switch (dir) {
	case CAM_ROT_YAW:
		N = rotate(N, angle, U);
		break;
	case CAM_ROT_PITCH:
		N = rotate(N, angle, V);
		break;
	}

	pointCamera( pos, N, U);
}


/* pointCamera( vec3, vec3);
 - parameters: target vector and up vector
 - returns: VOID
 - s.e.: builds the camera space matrix 
*/
GLvoid Camera::pointCamera( vec3 p, vec3 target, vec3 up) {
	pos = p;
	N = normalize(target);
	U = normalize(up);
	V = normalize(cross(N, U));
	camSpace = lookAt(pos, pos + N, U);
}


