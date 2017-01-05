#include "triangle.h"

GLuint gVAO, gVBO, gEBO;
using namespace glm;

void initTriangle() {
	vec3 vertices[] = {
		vec3(  0.5,  0.5, 0.0),
		vec3(  0.5, -0.5, 0.0),
		vec3( -0.5, -0.5, 0.0),
		vec3( -0.5,  0.5, 0.0)
	};
	GLuint indices[] = {
		0, 1, 3,
		1, 2, 3
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
	// creating new element buffer object (EBO)
	GLuint ebo;
	glGenBuffers(1, &ebo);

	// configuring vao
	glBindVertexArray(vao);
		// copying vertices array on GPU ( contained by vbo)
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		// sending position vertices
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		// copying element array on GPU ( ebo)
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// unbinding to avoid misconfiguration
	glBindVertexArray(0);

	gVAO = vao;
	gVBO = vbo;
	gEBO = ebo;
}

void display() {
	// clearing screen
	glClear(GL_COLOR_BUFFER_BIT);

	// drawing triangle
	glBindVertexArray(gVAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}