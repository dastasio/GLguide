#include "global.h"

using namespace std;

int main( int argc, char* argv[]) {
	
		GLFWwindow* window;
		if( !glfwInit()) exit( EXIT_FAILURE);
		window = glfwCreateWindow( 1024, 768, "glfw", NULL, NULL);
		if( !window) {
			glfwTerminate();
			exit( EXIT_FAILURE);
		}
	glfwMakeContextCurrent( window);

	// getting version info
	const GLubyte* p = glGetString( GL_VERSION);
	cout << "OpenGL Version: " << p << endl;
	return 0;
}

