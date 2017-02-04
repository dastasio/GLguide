#include <stdlib.h>
#include <stdio.h>
#include "global.h"

using namespace std;

int main(int argc, char* argv[]) {
	SDL_SetMainReady();

	App* cubeApp = new App();
	
	cubeApp->loop();
	
	SDL_Quit();
	return 0;
}