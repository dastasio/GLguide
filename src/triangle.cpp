#include "triangle.h"

using namespace glm;
mat4 model, view, projection;
GLuint gProgram, gVAO, gVBO, gEBO, gTex[2];
GLint mLoc, vLoc, pLoc;

void initTriangle( GLfloat w, GLfloat h) {
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


	// creating transformation matrices
	model = rotate(model, radians(-55.f), vec3(1.0, 0.0, 0.0));
	view = translate(view, vec3(0.0, 0.0, -3.0));
	projection = perspective(radians(45.f), w / h, 0.1f, 100.0f);

	
	// loading texture file container.jpg
	gTex[0] = loadTexture("container.jpg");
	gTex[1] = loadTexture("awesomeface.png");
	
	// compiling shaders
	gProgram = InitShader();
	glUseProgram(gProgram);
	
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


	// finding matrices locations
	mLoc = glGetUniformLocation(gProgram, "model");
	vLoc = glGetUniformLocation(gProgram, "view");
	pLoc = glGetUniformLocation(gProgram, "projection");
}

void display() {
	// sending transformation matrices
	glUniformMatrix4fv(mLoc, 1, GL_FALSE, &model[0][0]);
	glUniformMatrix4fv(vLoc, 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(pLoc, 1, GL_FALSE, &projection[0][0]);

	// clearing screen
	glClear(GL_COLOR_BUFFER_BIT);

	// drawing triangle
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, gTex[0]);
	glUniform1i(glGetUniformLocation(gProgram, "mTexture1"), 0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, gTex[1]);
	glUniform1i(glGetUniformLocation(gProgram, "mTexture2"), 1);


	glBindVertexArray(gVAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void initTexture() {
	// setting parameters for texture wrapping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	
	// setting parameters for texture sampling
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}


mat4 transform(vec3 t = vec3(0,0,0), GLfloat angl = 0.0, vec3 s = vec3(1,1,1)) {
	mat4 matrix = mat4(1.0);

	// scaling
	matrix = scale(matrix, s);
	// rotating
	matrix = rotate(matrix, angl, vec3(0.0, 0.0, 1.0));
	// translating
	matrix = translate(matrix, t);

	return matrix;
}