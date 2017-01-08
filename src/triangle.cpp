#include "triangle.h"

GLuint gVAO, gVBO, gEBO, gTex;
using namespace glm;

void initTriangle() {
	vec2 vertices[] = {
		// positions		| texture coordinates
		vec2( -0.5, -0.5),	vec2(  0.0,  0.0),	// bottom left
		vec2(  0.5, -0.5),	vec2(  1.0,  0.0),	// bottom right
		vec2(  0.5,  0.5),	vec2(  1.0,  1.0),	// top right
		vec2( -0.5,  0.5),	vec2(  0.0,  1.0)	// top left
	};
	GLuint indices[] = {
		0, 1, 3,	// first triangle
		1, 2, 3,	// second triangle
	};
	vec3 colors[] = {
		vec3( 1.0, 0.0, 0.0),
		vec3( 0.0, 1.0, 0.0),
		vec3( 0.0, 0.0, 1.0),
		vec3( 1.0, 1.0, 0.0)
	};
	
	// loading texture file container.jpg
	gTex = loadTexture("container.jpg");
	
	// compiling shaders
	GLuint program = InitShader();
	glUseProgram(program);
	
	// creating new Vertex Buffer Object (VBO)
	glGenBuffers(1, &gVBO);
	// creating new Vertex Array Object (VAO)
	glGenVertexArrays(1, &gVAO);
	// creating new Element Buffer Object (EBO)
	glGenBuffers(1, &gEBO);
	
	// configuring vao
	glBindVertexArray(gVAO);
		// copying vertices array on GPU ( contained by vbo)
		glBindBuffer(GL_ARRAY_BUFFER, gVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(colors), vertices, GL_STATIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(colors), colors);
		// sending position vertices
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(vec2), BUFFER_OFFSET(0));
		glEnableVertexAttribArray(0);
		// sending texture coordinates
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(vec2), BUFFER_OFFSET(sizeof(vec2)));
		glEnableVertexAttribArray(1);
		// setting color attribute pointer
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vertices)));
		glEnableVertexAttribArray(2);
		// setting element buffer object
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gEBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// unbinding to avoid misconfiguration
	glBindVertexArray(0);

}

void display() {
	// clearing screen
	glClear(GL_COLOR_BUFFER_BIT);

	// drawing triangle
	glBindTexture(GL_TEXTURE_2D, gTex);
	glBindVertexArray(gVAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void initTexture() {
	// setting parameters for texture wrapping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	
	// setting parameters for texture sampling
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}