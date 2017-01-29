#include "camera.h"

using namespace glm;

Camera::Camera() {
	camSpace = mat4(1.0);
	pos = vec3(0.0, 0.0, 3.0);

	//U = normalize(vec3(0.0, 1.0, 0.0));
	//N = normalize(vec3(1.0, 0.0, 0.0));
	//V = normalize(cross(N, U));

	pointCamera(pos,pos + vec3(0.0, 0.0,-1.0), vec3( 0.0, 1.0, 0.0));
}

Camera::~Camera() {
	delete &pos;
	delete &U;
	delete &V;
	delete &N;
}


/* move( vec3);
 - parameters: vec3 Cameraect representing wanted motion on x, y, z axis
 - returns: VOID
 - s.e.: updates private 'pos' vector with camera new position
*/
GLvoid Camera::move( GLboolean hor, GLfloat speed) {
	if (hor) {
		pos += normalize(cross(N, U)) * speed;
	}
	else {
		pos += N * speed;
	}

	pointCamera( pos, N, U);
}


/* turn( GLboolean, GLfloat);
 - parameters: bool indicating direction of rotation; angle of rotation
 - returns: VOID
 - s.e.: calls pointCamera
*/
GLvoid Camera::turn( GLboolean vertical, GLfloat angle) {
	mat4 r;
	// if rotation is horizontal
	if (!vertical) {
		// rotate target vector along UP vector by given angle
		r = rotate(mat4(1.0), angle, vec3(0.0, 1.0, 0.0));
		vec4 tmp = r * vec4(N, 1.0);
		N = vec3(tmp.x, tmp.y, tmp.z);
	}
	// if rotation is vertical
	else {
		// rotate target and up vectors along RIGHT vector by given angle
		r = rotate(mat4(1.0), angle, vec3(1.0, 0.0, 0.0));
		vec4 tmp = r * vec4(N, 1.0);
		N = vec3(tmp.x, tmp.y, tmp.z);
		tmp = r * vec4(U, 1.0);
		U = vec3(tmp.x, tmp.y, tmp.z);
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
	camSpace = lookAt(p, p - target, up);
}


