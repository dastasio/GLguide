#include "triangle.h"

GLuint gVAO, gVBO, gEBO;
using namespace glm;

void initTriangle() {
	vec3 vertices[] = {
		vec3( -0.75, -0.5, 0),
		vec3( -0.375, 0.5, 0),
		vec3(  0.00, -0.5, 0),
		vec3(  0.00, -0.5, 0),
		vec3(  0.375, 0.5, 0),
		vec3(  0.75, -0.5, 0)
	};
	
	// compiling shaders
	GLuint program = InitShader("shader.vert", "shader.frag");
	glUseProgram(program);

	// creating new Vertex Buffer Object (VBO)
	GLuint vbo;
	glGenBuffers(1, &vbo);
	// creating new Vertex Array Object (VAO)
	GLuint vao;
	glGenVertexArrays(1, &vao);

	// configuring vao
	glBindVertexArray(vao);
		// copying vertices array on GPU ( contained by vbo)
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		// sending position vertices
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), (GLvoid*)0);
		glEnableVertexAttribArray(0);
	// unbinding to avoid misconfiguration
	glBindVertexArray(0);

	gVAO = vao;
	gVBO = vbo;
}

void display() {
	// clearing screen
	glClear(GL_COLOR_BUFFER_BIT);

	// drawing triangle
	glBindVertexArray(gVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}