#include "dav_sdl.h"

SDL_Window* initSDL( SDL_GLContext &context,GLint w, GLint h) {

	// initializing SDL_VIDEO
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cerr << "ERROR: Could not initialize SDL_VIDEO!\n" << SDL_GetError();
		exit(EXIT_FAILURE);
	}
	else {
		// OpenGL context settings
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		// if SDL has initialized, create window
		SDL_Window* window = SDL_CreateWindow("OPENGL CUBE", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, 
				SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
		if (window == nullptr) {
			std::cerr << "ERROR: Could not create SDL window!\n" << SDL_GetError();
			exit(EXIT_FAILURE);
		}
		else {
			// creating opengl context
			context = SDL_GL_CreateContext(window);
			
			if (context == NULL) {
				std::cerr << "ERROR: Could not create an OpenGL 3.3 Context!\n" << SDL_GetError();
				exit(EXIT_FAILURE);
			}
			else {
				// if context created successfully, init GLEW
				SDL_GL_MakeCurrent(window, context);
#if not defined __APPLE__
				glewExperimental = GL_TRUE;
				GLenum gErr = glewInit();
				if (gErr != GLEW_OK) {
					std::cerr << "ERROR: Could not initialize GLEW!\n" << glewGetErrorString(gErr);
				}
#endif

				// if window creation successful, init SDL_IMAGE
				GLint flags = IMG_INIT_PNG | IMG_INIT_JPG;
				if (!(IMG_Init(flags) & flags)) {
					std::cerr << "ERROR: SDL_image could not initialize!\n" << IMG_GetError();
					exit(EXIT_FAILURE);
				}
				else {
					std::cout << "INIT SUCCESS: SDL initialized successfully!\n";
					glViewport(0, 0, w, h);
					return window;
				}
			}
		}
	}
}
