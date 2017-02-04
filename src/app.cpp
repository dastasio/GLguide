#include "app.h"

using namespace glm;

Camera* cam = new Camera( vec3(0.0, 0.3, 3.0));
Obj* cube;
Obj* floorModel;

App::App() {
	model = mat4(1.0);
	view = cam->getMatrix();
	projection = mat4(1.0);

	initCube();
	initWindow();
	initBuffers();
	initMatrices();
    
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
    
	locModel = glGetUniformLocation(gProgram, "model");
	locView = glGetUniformLocation(gProgram, "view");
	locProj = glGetUniformLocation(gProgram, "projection");
	locLightCol = glGetUniformLocation(gProgram, "lightColor");
	locObjCol = glGetUniformLocation(gProgram, "objColor");

	ligModel = glGetUniformLocation(lightProgram, "model");
	ligView = glGetUniformLocation(lightProgram, "view");
	ligProj = glGetUniformLocation(lightProgram, "projection");
}

App::~App() {
	// deallocating memory

	delete &VAO;
	delete &VBO;
	
	delete cam;
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
- s.e.: initializes projection matrix
*/
GLvoid App::initProjection(GLfloat fov, GLfloat ar) {
	projection = perspective(fov, ar, 0.1f, 500.0f);
}




/* initBuffers();
- parameters: VOID
- returns: VOID
- s.e.: creates vertex buffer object, vertex array object
		and element buffer object
*/
GLvoid App::initBuffers() {
	// linking shaders
	gProgram = modelShader();
	lightProgram = lightShader();
	glUseProgram(gProgram);

	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &lightVAO);
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &EBO);

	for (int i = 0; i < (cube->Count() + floorModel->Count()) ; ++i) {
		indices.push_back(i);
	}
	
	// VAO setup
	glBindVertexArray(VAO);
		// sending cube data to GPU
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, cube->Capacity() + floorModel->Capacity(), nullptr, GL_STATIC_DRAW);
		GLsizeiptr off = cube->sendData(0);
		floorModel->sendData(off);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), BUFFER_OFFSET(0));
		glEnableVertexAttribArray(0);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// setting up ligth VAO
	glBindVertexArray(lightVAO);
		glBindBuffer( GL_ARRAY_BUFFER, VBO);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), BUFFER_OFFSET(0));
		glEnableVertexAttribArray(0);
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

	// projection matrix
	initProjection();
}


/* render();
 - parameters: VOID
 - returns: VOID
 - s.e.: renders cube to screen
		sends uniform variables to GLSL
*/
GLvoid App::render() {
	glEnable(GL_DEPTH_TEST);

	glUseProgram(gProgram);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// sending matrices
	glUniformMatrix4fv(locView, 1, GL_FALSE, value_ptr(view));
	glUniformMatrix4fv(locProj, 1, GL_FALSE, value_ptr(projection));
	glUniformMatrix4fv(ligView, 1, GL_FALSE, value_ptr(view));
	glUniformMatrix4fv(ligProj, 1, GL_FALSE, value_ptr(projection));
	glUniform3f(locLightCol, 1.0, 1.0, 1.0);
	glUniform3f(locObjCol, 1.0, 0.5, 0.31);

	
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// drawing cubes
	model = mat4(1.0);
	glUniformMatrix4fv(locModel, 1, GL_FALSE, value_ptr(model));
	glDrawElements(GL_TRIANGLES, cube->Count(), GL_UNSIGNED_INT, 0);
	// drawing floor
	model = translate(mat4(1.0), vec3(0.0, -0.51, 0.0));
	model = scale(model, vec3(3.0));
	glUniformMatrix4fv(locModel, 1, GL_FALSE, value_ptr(model));
	glDrawElements(GL_TRIANGLES, floorModel->Count(), GL_UNSIGNED_INT, cube->Offset());
	
	glBindVertexArray(0);


	glUseProgram(lightProgram);
	glBindVertexArray(lightVAO);

	model = translate(mat4(1.0), lightPos);
	model = scale(model, vec3(0.2));
	glUniformMatrix4fv(ligModel, 1, GL_FALSE, value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, cube->Count());
	
	glBindVertexArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	SDL_GL_SwapWindow(thisWindow);
}


GLvoid App::loop() {

	SDL_Event ev;
	GLboolean run = GL_TRUE;
	while ( run) {
		SDL_GL_SetSwapInterval(1);
		SDL_PollEvent(&ev);
		if (ev.type == SDL_QUIT) {
			run = GL_FALSE;
		}
		render();
		run = grabInput();

		view = cam->getMatrix();
	}
}


GLboolean App::grabInput() {
	SDL_SetRelativeMouseMode(SDL_TRUE);

	GLbitfield mouseState;
	GLint mX, mY;
	const GLubyte* keystate = SDL_GetKeyboardState(nullptr);
	static GLfloat fov = radians(45.0f);

	GLfloat speed = 0.2;
	// reading keyboard input
	if (keystate[SDL_SCANCODE_UP]) {
		fov += 0.05;
		if (fov >= M_PI / 2) fov = M_PI / 2;
		initProjection(fov);
	}
	if (keystate[SDL_SCANCODE_DOWN]) {
		fov -= 0.05;
		if (fov <= 0.1) fov = 0.1;
		initProjection(fov);
	}
	if (keystate[SDL_SCANCODE_ESCAPE]) {
		return GL_FALSE;
	}
	if (keystate[SDL_SCANCODE_W]) {
		cam->move(CAM_MOVE_FORWARD, speed);
	}
	if (keystate[SDL_SCANCODE_S]) {
		cam->move(CAM_MOVE_FORWARD, -speed);
	}
	if (keystate[SDL_SCANCODE_A]) {
		cam->move(CAM_MOVE_RIGHT, -speed);
	}
	if (keystate[SDL_SCANCODE_D]) {
		cam->move(CAM_MOVE_RIGHT, speed);
	}
	if (keystate[SDL_SCANCODE_LSHIFT]) {
		cam->move(CAM_MOVE_UP, speed);
	}
	if (keystate[SDL_SCANCODE_LCTRL]) {
		cam->move(CAM_MOVE_UP, -speed);
	}

	// reading mouse input
	mouseState = SDL_GetRelativeMouseState(&mX, &mY);
	cam->turn(CAM_ROT_YAW, -(mX / width) * 2 * M_PI);
	cam->turn(CAM_ROT_PITCH, -(mY / height) * 2 * M_PI);
	return GL_TRUE;
}


GLvoid App::initCube() {
	GLfloat cubeVerts[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};
	GLfloat floorVerts[] = {
		-10.0, 0.0,  10.0,	0.0, 0.0,
		 10.0, 0.0,  10.0,  1.0, 0.0,
		 10.0, 0.0, -10.0,  1.0, 1.0,
		 10.0, 0.0, -10.0,  1.0, 1.0,
		-10.0, 0.0, -10.0,  0.0, 1.0,
		-10.0, 0.0,  10.0,  0.0, 0.0
	};

	cube = new Obj(cubeVerts, sizeof(cubeVerts) / sizeof(GLfloat));
	floorModel = new Obj(floorVerts, sizeof(floorVerts) / sizeof(GLfloat));
}
