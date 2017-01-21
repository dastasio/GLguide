#include <stdlib.h>
#include <stdio.h>
#include "global.h"

using namespace std;

int main(int argc, char* argv[]) {
	SDL_SetMainReady();

	//App* cubeApp = new App();
	//
	//cubeApp->loop();
	
	SDL_GLContext context;
	SDL_Window* window = initSDL(context);
	
	for (int i = 0; i < 3; ++i) {
		glClear(GL_COLOR_BUFFER_BIT);
		SDL_GL_SwapWindow(window);
	
		SDL_Delay(2000);
	}

	SDL_Quit();

	return 0;
}