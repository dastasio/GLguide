#include <stdlib.h>
#include <stdio.h>
#include "global.h"

using namespace std;

int main( int argc, char* argv[]) {
	
	int w = 1024, h = 768;
		GLFWwindow* window;
		if( !glfwInit()) exit( EXIT_FAILURE);
		window = glfwCreateWindow( w, h, "glfw", NULL, NULL);
		if( !window) {
			glfwTerminate();
			exit( EXIT_FAILURE);
		}
	glfwMakeContextCurrent( window);

	// initializing glew
	glewExperimental = GL_FALSE;
	GLenum glewError = glewInit();
	if (glewError != GLEW_OK) {
		printf("glew init error\n%s\n", glewGetErrorString(glewError));
	}

	if (!GLEW_VERSION_2_1) {
		printf("OpenGL 2.1 not supported!");
		return false;
	}

	// getting opengl and glsl version strings
	const GLubyte* p = glGetString(GL_VERSION);
	cout << "Graphics Driver: " << p << endl;

	const GLubyte* q = glGetString(GL_SHADING_LANGUAGE_VERSION);
	cout << "GLSL Version: " << q << endl;


	// checking for functionalities
	if (GLEW_ARB_vertex_array_object) {
		printf("genVertexArrays supported\n");
	}
	if (GLEW_APPLE_vertex_array_object) {
		printf("genVertexArrayApple supported\n");
	}


	while( !glfwWindowShouldClose( window)) {
		glViewport( 0, 0, w, h);
		glClearColor( 0.2, 0.4, 0.5, 1.0);
		glClear( GL_COLOR_BUFFER_BIT);

		// draw code

		glfwSwapBuffers( window);
		glfwPollEvents();
	}
	

	glfwDestroyWindow( window);
	glfwTerminate();

	return 0;
}
