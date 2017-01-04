#include "glfw_wind.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	// closing if ESC is pressed
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}