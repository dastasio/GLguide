#include "cube.h"

using namespace glm;

App::App() {
	model = mat4(1.0);
	view = mat4(1.0);
	projection = mat4(1.0);


	resizable = GL_FALSE;

	initWindow();
	initCube();
	initBuffers();
	initMatrices();
	initTexture();

	//texSmile = loadTexture("awesomeface.png");
	//texCont = loadTexture("container.jpg");

	locModel = glGetUniformLocation(gProgram, "model");
	locView = glGetUniformLocation(gProgram, "view");
	locProj = glGetUniformLocation(gProgram, "projection");
}

App::~App() {
	// deallocating memory

	delete &VAO;
	delete[] BO;
}




/* initWindow();
- parameters: VOID
- returns: VOID
- s.e.: starts a window using GLFW
*/
GLvoid App::initWindow() {
	thisWindow = initSDL();

	// setting clear color
	glClearColor(0.2, 0.45, 0.5, 1.0);
}




/* initCube();
- parameters: VOID
- returns: VOID
- s.e.: initializes cube vertices in vec3 array (cube)
		and texture coordinates in vec2 array (texCoordinates)
		and texture object
*/
GLvoid App::initCube() {
	
	// setting up coordinates
	cube = {
		vec3( -0.5, -0.5,  0.5),	vec3(  0.5, -0.5,  0.5),	// 0  1
		vec3(  0.5,  0.5,  0.5),	vec3( -0.5,  0.5,  0.5),	// 2  3

		vec3( -0.5, -0.5, -0.5),	vec3(  0.5, -0.5, -0.5),	// 4  5
		vec3(  0.5,  0.5, -0.5),	vec3( -0.5,  0.5, -0.5)		// 6  7
	};

	texCoordinates = {
		vec2(  0.0,  0.0),	vec2(  1.0,  0.0),	// 0  1
		vec2(  1.0,  1.0),	vec2(  0.0,  1.0),	// 2  3

		vec2(  1.0,  1.0),	vec2(  0.0,  1.0),	// 4  5
		vec2(  0.0,  0.0),	vec2(  1.0,  0.0)	// 6  7
	};

	// setting up vertex indices
	indices = {
		0, 1, 2,	2, 3, 0,
		0, 3, 4,	4, 3, 7,
		1, 5, 6,	6, 2, 1,
		4, 5, 6,	6, 7, 4,
		5, 1, 0,	0, 4, 5,
		3, 7, 6,	6, 2, 3
	};
}




/* initBuffers();
- parameters: VOID
- returns: VOID
- s.e.: creates vertex buffer object, vertex array object
		and element buffer object
*/
GLvoid App::initBuffers() {
	// linking shaders
	gProgram = InitShader();
	glUseProgram(gProgram);

	glGenBuffers(2, BO);
	glGenVertexArrays(1, &VAO);

	// sending cube data to GPU
	glBindBuffer( GL_ARRAY_BUFFER, BO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube) + sizeof(texCoordinates), &cube, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(cube), sizeof(texCoordinates), &texCoordinates);
	// VAO setup
	glBindVertexArray(VAO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(cube)));

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BO[1]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}





/* initMatrices();
- parameters: VOID
- returns: VOID
- s.e.: initializes matrices ( model, view, projection)
		which will be used to get from object coordinates
		to window coordinates
*/
GLvoid App::initMatrices() {
	// model matrix stays I

	// view matrix
	view = translate(view, vec3(0.0, 0.0, -3.0));

	// projection matrix
	projection = perspective(45.f, GLfloat(width / height), 0.1f, 100.f);
}


/* initTexture();
 - parameters: VOID
 - returns: VOID
 - s.e.: initializes texture settings
*/
GLvoid App::initTexture() {
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}


/* render();
 - parameters: VOID
 - returns: VOID
 - s.e.: renders cube to screen
		sends uniform variables to GLSL
*/
GLvoid App::render() {
	glClear(GL_COLOR_BUFFER_BIT);
	
	// setting textures
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texCont);
	glUniform1i(glGetUniformLocation(gProgram, "texContainer"), 0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texSmile);
	glUniform1i(glGetUniformLocation(gProgram, "texSmile"), 1);
	
	// sending matrices
	glUniformMatrix4fv(locModel, 1, GL_FALSE, value_ptr(model));
	glUniformMatrix4fv(locView, 1, GL_FALSE, value_ptr(view));
	glUniformMatrix4fv(locProj, 1, GL_FALSE, value_ptr(projection));
	
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 54, GL_INT, 0);
	glBindVertexArray(0);

	SDL_GL_SwapWindow(thisWindow);
}


GLvoid App::loop() {
	while (true) {
		render();

		// rotating cube
		model = rotate(model, radians(0.5f), vec3(0.5, 1.0, 0.0));
	}
}