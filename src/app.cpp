#include "app.h"

using namespace glm;

Camera* cam = new Camera( vec3(0.0, 0.3, 3.0));
Obj* cube;
Obj* floorModel;

App::App() {
	model = mat4(1.0);
	view = cam->getMatrix();
	projection = mat4(1.0);


	initWindow();
	initCube();
	initBuffers();
	initMatrices();
	
	nanosuit = new Model("models/nanosuit2.obj");
    
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
    
	locModel = glGetUniformLocation(gProgram, "model");
	locView = glGetUniformLocation(gProgram, "view");
	locProj = glGetUniformLocation(gProgram, "projection");
	locViewPos = glGetUniformLocation(gProgram, "viewPos");

	ligModel = glGetUniformLocation(lightProgram, "model");
	ligView = glGetUniformLocation(lightProgram, "view");
	ligProj = glGetUniformLocation(lightProgram, "projection");
	ligPos = glGetUniformLocation(gProgram, "lightPos");
	
	matDiffLoc = glGetUniformLocation(gProgram, "mater.diffuse");
	matSpecLoc = glGetUniformLocation(gProgram, "mater.specular");
	matShineLoc = glGetUniformLocation(gProgram, "mater.shineFactor");
	
	dirDirLoc = glGetUniformLocation(gProgram, "dirL.direction");
	dirAmbLoc = glGetUniformLocation(gProgram, "dirL.amb");
	dirDiffLoc = glGetUniformLocation(gProgram, "dirL.diff");
	dirSpecLoc = glGetUniformLocation(gProgram, "dirL.spec");
	
	for( long i = 0; i < 4; ++i) {
		std::string name = "pointL[";
		std::ostringstream conv;
		conv << i;
		
		name.append(conv.str());
		name.append("].position");
		pntPosLoc[i] = glGetUniformLocation(gProgram, name.c_str());
		
		name.clear();
		name = "pointL[";
		name.append(conv.str());
		name.append("].constant");
		pntConstLoc[i] = glGetUniformLocation(gProgram, name.c_str());
		
		name.clear();
		name = "pointL[";
		name.append(conv.str());
		name.append("].linear");
		pntLinLoc[i] = glGetUniformLocation(gProgram, name.c_str());
		
		name.clear();
		name = "pointL[";
		name.append(conv.str());
		name.append("].quadratic");
		pntQuadLoc[i] = glGetUniformLocation(gProgram, name.c_str());
		
		name.clear();
		name = "pointL[";
		name.append(conv.str());
		name.append("].amb");
		pntAmbLoc[i] = glGetUniformLocation(gProgram, name.c_str());
		
		name.clear();
		name = "pointL[";
		name.append(conv.str());
		name.append("].diff");
		pntDiffLoc[i] = glGetUniformLocation(gProgram, name.c_str());
		
		name.clear();
		name = "pointL[";
		name.append(conv.str());
		name.append("].spec");
		pntSpecLoc[i] = glGetUniformLocation(gProgram, name.c_str());
	}
	
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
	glClearColor(0.1, 0.1, 0.1, 1.0);

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
	
//	// VAO setup
//	{
//		glBindVertexArray(VAO);
//		// sending cube data to GPU
//		glBindBuffer(GL_ARRAY_BUFFER, VBO);
//		glBufferData(GL_ARRAY_BUFFER, cube->Capacity() + floorModel->Capacity(), nullptr, GL_STATIC_DRAW);
//		GLsizeiptr off = cube->sendData(0);
//		floorModel->sendData(off);
//
//		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
//
//		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), BUFFER_OFFSET(0));
//		glEnableVertexAttribArray(0);
//		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), BUFFER_OFFSET(3 * sizeof(GLfloat)));
//		glEnableVertexAttribArray(1);
//		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), BUFFER_OFFSET(6 * sizeof(GLfloat)));
//		glEnableVertexAttribArray(2);
//		glBindVertexArray(0);
//		glBindBuffer(GL_ARRAY_BUFFER, 0);
//	}
	
	// setting up ligth VAO
	{
		glBindVertexArray(lightVAO);
		glBindBuffer( GL_ARRAY_BUFFER, VBO);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), BUFFER_OFFSET(0));
		glEnableVertexAttribArray(0);
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
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
	{
		glUniformMatrix4fv(locView, 1, GL_FALSE, value_ptr(view));
		glUniformMatrix4fv(locProj, 1, GL_FALSE, value_ptr(projection));
		vec3 viewPos = cam->getPosition();
		glUniform3f(locViewPos, viewPos.x, viewPos.y, viewPos.z);
		
		glUniform1i(matDiffLoc, 0);
		glUniform1i(matSpecLoc, 1);
		glUniform1f(matShineLoc, 512);
		
		
		glUniform3f(dirDirLoc, 0.0, 2.0, 3.0);
		glUniform3f(dirAmbLoc, 0.05, 0.05, 0.02);
		glUniform3f(dirDiffLoc, 0.4, 0.4, 0.25);
		glUniform3f(dirSpecLoc, 0.5, 0.5, 0.4);
		
	}
	
	// rendering scene
	{
//		glBindVertexArray(VAO);
//		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		
		
		nanosuit->Draw(gProgram);
		
		
//		glBindVertexArray(0);
	}
	
	
	

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
    SDL_ShowCursor(SDL_FALSE);
	
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
	if (keystate[SDL_SCANCODE_RSHIFT]) {
		speed = 0.05;
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
}












