#pragma once
#include "global.h"

using namespace glm;

class Obj {
public:
	Obj( GLfloat* data, GLsizeiptr size);
	~Obj();

	GLsizeiptr sendData( GLuint offset);

	GLsizeiptr Size() { return count; }
private:
	vec3 position;
	GLsizeiptr count;

	std::vector<GLfloat> verts;
};