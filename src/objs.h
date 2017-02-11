#pragma once
#include "global.h"

using namespace glm;

class Obj {
public:
	Obj( GLfloat* data, GLsizeiptr size);
	~Obj();

	GLsizeiptr sendData( GLuint dataOffset);

	GLsizeiptr Capacity() { return Size() * sizeof(GLfloat); }
	GLsizeiptr Size() { return verts.size(); }
	GLsizeiptr Count() { return verts.size() / 8; }
	GLvoid* Offset() { return BUFFER_OFFSET(Count() * sizeof(GLfloat)); }
private:
	vec3 position;


	std::vector<GLfloat> verts;
};
