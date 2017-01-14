#include <stdlib.h>
#include <stdio.h>
#include "global.h"

using namespace std;

int main( int argc, char* argv[]) {
	// initalizing GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(960, 960, "Hello GLFW!", nullptr, nullptr);
	if (window == nullptr) {
		printf("Failed to create GLFW window!");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// initializing GLEW
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		printf("Failed to initalize GLEW!");
		return -1;
	}

	// setting OpenGL viewport
	int w, h;
	glfwGetFramebufferSize(window, &w, &h);
	glViewport(0, 0, w, h);

	// setting key callback function
	glfwSetKeyCallback(window, key_callback);

	// setting clear color
	glClearColor(0.2, 0.45, 0.5, 1.0);

	initTriangle();

	// program loop
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		// rendering screen
		display();

		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}