#include "app.h"
#include "dav_sdl.h"
#include "common.h"

#define FOV radians(45.0f)
#define AR	1.42f

using namespace glm;


App::App() {
	initWindow();
	
	cam = new Camera();
	initBuffers();
	initMatrices();
	
}

App::~App() {

}




/* initWindow();
- parameters: VOID
- returns: VOID
- s.e.: starts a window using SDL2
*/
GLvoid App::initWindow() {
	// creating window and setting viewport
	main_window = initSDL( main_context, main_width, main_height);
	glViewport(0, 0, main_width, main_height);
	
	
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
	projection = perspective(FOV, AR, 0.1f, 500.0f);
}




/* initBuffers();
- parameters: VOID
- returns: VOID
- s.e.: creates vertex buffer object, vertex array object
		and element buffer object
*/
GLvoid App::initBuffers() {
	// linking shaders
	this->program = modelShader();
	glUseProgram(this->program);
	
	suit = new davModel("models/wolf.dae");
	
	
	locModel = glGetUniformLocation(this->program, "model");
	locProj = glGetUniformLocation(this->program, "projection");
	locView = glGetUniformLocation(this->program, "view");
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
	model = mat4(1.0);

	view = cam->getMatrix();
	
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

	glUseProgram(program);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// sending matrices
	{
		glUniformMatrix4fv(locView, 1, GL_FALSE, value_ptr(view));
		glUniformMatrix4fv(locProj, 1, GL_FALSE, value_ptr(projection));
		
		
		model = translate(mat4(1.0), vec3(0.0, -1.75, 0.0));
		model = scale(model, vec3(0.009));
		glUniformMatrix4fv(locModel, 1, GL_FALSE, value_ptr(model));
		
		
	}
	
	// rendering scene
	{
//		glBindVertexArray(VAO);
//		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		
		
		suit->Draw(program);
		
		
//		glBindVertexArray(0);
	}
	
	
	

	SDL_GL_SwapWindow(main_window);
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
	cam->turn(CAM_ROT_YAW, -(mX / main_width) * 2 * M_PI);
	cam->turn(CAM_ROT_PITCH, -(mY / main_height) * 2 * M_PI);
	
	return GL_TRUE;
}










