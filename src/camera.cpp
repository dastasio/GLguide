#include "camera.h"

using namespace glm;

Camera::Camera() {
	pos = vec3(0.0);

	U = normalize(vec3(0.0, 1.0, 0.0));
	N = normalize(vec3(1.0, 0.0, 0.0));
	V = normalize(cross(N, U));

	pointCamera(pos - N, U);
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
GLvoid Camera::move( vec3 m) {
	vec4 tmp = vec4(pos, 1.0);
	tmp = translate(mat4(1.0), m) * tmp;

	pos = vec3(tmp.x, tmp.y, tmp.z);
}


/* turn( GLboolean, GLfloat);
 - parameters: bool indicating direction of rotation; angle of rotation
 - returns: VOID
 - s.e.: calls pointCamera
*/
GLvoid Camera::turn( GLboolean vertical, GLfloat angle) {
	mat4 r;
	vec3 target = pos - N;
	// if rotation is horizontal
	if (!vertical) {
		// rotate target vector along UP vector by given angle
		r = rotate(mat4(1.0), angle, U);
		vec4 tmp = r * vec4(target, 1.0);
		target = vec3(tmp.x, tmp.y, tmp.z);
	}
	// if rotation is vertical
	else {
		// rotate target and up vectors along RIGHT vector by given angle
		r = rotate(mat4(1.0), angle, V);
		vec4 tmp = r * vec4(target, 1.0);
		target = vec3(tmp.x, tmp.y, tmp.z);
		tmp = r * vec4(U, 1.0);
		U = vec3(tmp.x, tmp.y, tmp.z);
	}

	pointCamera( target, U);
}


/* pointCamera( vec3, vec3);
 - parameters: target vector and up vector
 - returns: VOID
 - s.e.: builds the camera space matrix 
*/
GLvoid Camera::pointCamera( vec3 target, vec3 up) {
	N = normalize(pos - target);
	U = normalize(up);
	V = cross(N, U);
	camSpace = lookAt(pos, N, U);
}