#include "objs.h"

Obj::Obj(GLfloat* data, GLsizeiptr size) {
	verts.resize(size);
	for (int i = 0; i < size; ++i) {
		verts[i] = *data;
		data++;
	}
}

Obj::~Obj() {
	delete &position;
	verts.clear();
}



/* sendData();
 - parameters: offset value
 - returns: size of sent data
 - s.e.: NONE
*/
GLsizeiptr Obj::sendData( GLuint dataOffset) {
	glBufferSubData(GL_ARRAY_BUFFER, dataOffset, Capacity(), verts.data());

	return Capacity();
}