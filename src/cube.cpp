#include "cube.h"

using namespace glm;

App::App() {
	model = mat4(1.0);
	view = mat4(1.0);
	projection = mat4(1.0);

	initWindow();
	initCube();
	initBuffers();
	initMatrices();

	locModel = glGetUniformLocation(gProgram, "model");
	locView = glGetUniformLocation(gProgram, "view");
	locProj = glGetUniformLocation(gProgram, "projection");
}

App::~App() {
	// deallocating memory

	delete &VAO;
	delete &VBO;
}




/* initWindow();
- parameters: VOID
- returns: VOID
- s.e.: starts a window using GLFW
*/
GLvoid App::initWindow() {
	thisWindow = initSDL( thisContext, width, height);

	glViewport(0, 0, width, height);
	// setting clear color
	glClearColor(0.2, 0.45, 0.5, 1.0);

	// setting depth buffer test
	glEnable(GL_DEPTH_TEST);
}


/* initCube();
- parameters: VOID
- returns: VOID
- s.e.: initializes cube vertices and texture coordinates 
		in GLfloat array (cube)
*/
GLvoid App::initCube() {
	

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

	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);

	
	// VAO setup
	glBindVertexArray(VAO);
		// sending cube data to GPU
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(cube), cube, GL_STATIC_DRAW);
		initTexture();
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), BUFFER_OFFSET(0));
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), BUFFER_OFFSET( 3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);
	glBindVertexArray(0);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
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
	texSmile = loadTexture("awesomeface.jpg");
	texCont = loadTexture("container.jpg");
}


/* render();
 - parameters: VOID
 - returns: VOID
 - s.e.: renders cube to screen
		sends uniform variables to GLSL
*/
GLvoid App::render() {
	glUseProgram(gProgram);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
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
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	SDL_GL_SwapWindow(thisWindow);
}


GLvoid App::loop() {
	SDL_Event ev;
	GLboolean run = GL_TRUE;
	while ( run) {
		SDL_PollEvent(&ev);
		if (ev.type == SDL_QUIT) {
			run = GL_FALSE;
		}
		render();

		// rotating cube
		model = rotate(model, radians(0.5f), vec3(0.5, 1.0, 0.0));
	}
}