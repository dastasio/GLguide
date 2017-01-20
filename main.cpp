#include <stdlib.h>
#include <stdio.h>
#include "global.h"

using namespace std;

int main( int argc, char* argv[]) {
	// initalizing GLFW
	//glfwInit();

	App* cubeApp = new App();

	cubeApp->loop();

	//glfwTerminate();
	return 0;
}