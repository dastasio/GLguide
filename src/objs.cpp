#include "objs.h"

Obj::Obj(GLfloat* data, GLsizeiptr size) {
	count = size;

	verts.resize(count);
	for (int i = 0; i < size; ++i) {
		verts[i] = *data;
		data++;
	}
}

Obj::~Obj() {
	//delete &position;
	//delete &count;
	//verts.clear;
	//delete &verts;
}



/* sendData();
 - parameters: offset value
 - returns: size of sent data
 - s.e.: NONE
*/
GLsizeiptr Obj::sendData( GLuint offset) {
	glBufferSubData(GL_ARRAY_BUFFER, offset, count * sizeof(GLfloat), verts.data());

	return count;
}