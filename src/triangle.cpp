#include "triangle.h"

GLuint vao, vbo;
using namespace glm;

void initTriangle() {
	vec3 v1[] = {
		vec3( -0.5, -0.5 , 0),
		vec3(  0.0,  0.75, 0),
		vec3(  0.5, -0.5 , 0)
	};
	
	// compiling shaders
	GLuint program = InitShader();
	glUseProgram(program);

	// creating new Vertex Buffer Object (VBO)
	glGenBuffers(1, &vbo);
	// creating new Vertex Array Object (VAO)
	glGenVertexArrays(1, &vao);

	// configuring first vao
	glBindVertexArray(vao);
		// copying vertices array on GPU ( contained by vbo)
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(v1), v1, GL_STATIC_DRAW);
		// sending position vertices
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), (GLvoid*)0);
		glEnableVertexAttribArray(0);
	// unbinding to avoid misconfiguration
	glBindVertexArray(0);
}

void display() {
	// clearing screen
	glClear(GL_COLOR_BUFFER_BIT);

	// drawing triangle
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);
}