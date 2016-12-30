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

