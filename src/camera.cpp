#include "camera.h"

using namespace glm;

Camera::Camera( vec3 position) {
	camSpace = mat4(1.0);
	pos = position;

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
GLvoid Camera::move(camEnum dir, GLfloat speed) {
	GLfloat tmpY = pos.y;
	switch (dir) {
	case CAM_MOVE_RIGHT:
		pos += normalize(cross(N, U)) * speed;
		pos.y = tmpY;
		break;

	case CAM_MOVE_FORWARD:
		pos += N * speed;
		pos.y = tmpY;
		break;

	case CAM_MOVE_UP:
		pos += U * speed;
		break;
	default:
		break;
	}

	pointCamera(pos, N, U);
}


/* turn( GLboolean, GLfloat);
 - parameters: bool indicating direction of rotation; angle of rotation
 - returns: VOID
 - s.e.: calls pointCamera
*/
GLvoid Camera::turn(camEnum dir, GLfloat angle) {
    
	switch (dir) {
	case CAM_ROT_YAW:
		N = rotate(N, angle, U);
		break;
	case CAM_ROT_PITCH:
		// limiting up and down rotation
		if (N.y >= 0.8 && angle >= 0) angle = 0;
		else if (N.y <= -0.8 && angle <= 0) angle = 0;
		
		N = rotate(N, angle, V);
		break;
    default:
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


