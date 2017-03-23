#include <stdlib.h>
#include <stdio.h>
#include "global.h"
#include "ShaderMan.hpp"
#include "dav_sdl.h"

using namespace std;

int main(int argc, char* argv[]) {
	SDL_SetMainReady();

	den::ShaderMan* sman = new den::ShaderMan();
	
	SDL_GLContext cont;
	SDL_Window* window = initSDL(cont);
	glViewport(0, 0, 1024, 720);
	
	sman->CreateProgram("main", "shader.vert", "shader.frag");
	
	glUseProgram(sman->GetShader("main"));
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
	
	
	GLboolean run = GL_TRUE;
	while(run) {
		SDL_Event e;
		while(SDL_PollEvent(&e)) {
			if(e.type == SDL_QUIT)
				run = GL_FALSE;
		}
		
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		SDL_GL_SwapWindow(window);
	}
	
	SDL_Quit();
	return 0;
}
