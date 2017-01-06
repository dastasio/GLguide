#include "triangle.h"

GLuint gProgram[2];
GLuint vao[2], vbo[2];
using namespace glm;

void initTriangle() {
	vec3 v1[] = {
		vec3( -0.75, -0.5, 0),
		vec3( -0.375, 0.5, 0),
		vec3(  0.00, -0.5, 0)
	};
	vec3 v2[] = {
		vec3(  0.00, -0.5, 0),
		vec3(  0.375, 0.5, 0),
		vec3(  0.75, -0.5, 0)
	};
	
	// compiling shaders
	InitShader();
	glUseProgram(gProgram[0]);

	// creating new Vertex Buffer Object (VBO)
	glGenBuffers(2, vbo);
	// creating new Vertex Array Object (VAO)
	glGenVertexArrays(2, vao);

	// configuring first vao
	glBindVertexArray(vao[0]);
		// copying vertices array on GPU ( contained by vbo)
		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(v1), v1, GL_STATIC_DRAW);
		// sending position vertices
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), (GLvoid*)0);
		glEnableVertexAttribArray(0);
	// unbinding to avoid misconfiguration
	glBindVertexArray(0);

	// configuring second vao
	glBindVertexArray(vao[1]);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(v2), v2, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), (GLvoid*)0);
		glEnableVertexAttribArray(0);
	glBindVertexArray(0);

}

void display() {
	// clearing screen
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(gProgram[0]);
	// drawing triangle
	glBindVertexArray(vao[0]);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glUseProgram(gProgram[1]);
	glBindVertexArray(vao[1]);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);
}