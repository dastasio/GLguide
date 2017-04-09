#include <stdlib.h>
#include <stdio.h>
#include "global.h"
#include "ShaderMan.hpp"
#include "WindowMan.hpp"

using namespace std;

int main(int argc, char* argv[]) {
	SDL_SetMainReady();

	den::ShaderMan* sman = new den::ShaderMan();
	den::WindowMan* wman = new den::WindowMan();
	
	den::DEN_Window window;
	den::DEN_Context context;
	wman->CreateWindow(window, context);
	
	sman->CreateProgram("main", "shader.vert", "shader.frag");
	sman->Use("main");
	
	
	GLfloat triangle[] = {
		-0.75, -0.75, 0.0,
		 0.75, -0.75, 0.0,
		 0.0,   0.75, 0.0
	};
	
	GLuint vao, vbo;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	glEnableVertexAttribArray(0);
	
	
	wman->Loop();
	
	SDL_Quit();
	return 0;
}
