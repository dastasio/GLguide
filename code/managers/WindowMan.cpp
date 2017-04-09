#include "WindowMan.hpp"



GLvoid den::WindowMan::Loop() {
	SDL_bool running = SDL_TRUE;
	
	while(running) {
		SDL_Event e;
		SDL_PollEvent(&e);
		if (e.type == SDL_QUIT) {
			running = SDL_FALSE;
		}
		if (e.key.keysym.scancode == SDL_SCANCODE_F) {
			SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
		}
		else if (e.key.keysym.scancode == SDL_SCANCODE_E) {
		}
		
		
		render();
		
		SDL_GL_SwapWindow(this->window);
	}
}


GLvoid den::WindowMan::render() {
	glClearColor(0.1, 0.3, 0.3, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}








Uint32 den::WindowMan::SetWindowAttribs(den::DEN_Window &window, den::DEN_Context &context) {
	// context settings
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, context.v_major);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, context.v_minor);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	if (context.core_profile)
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
							SDL_GL_CONTEXT_PROFILE_CORE);
	else
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
							SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
	
	
	// window settings
	Uint32 window_flags = SDL_WINDOW_OPENGL;
	if (window.resizable)
		window_flags |= SDL_WINDOW_RESIZABLE;
	if (window.shown)
		window_flags |= SDL_WINDOW_SHOWN;
	
	return window_flags;
}


GLvoid den::WindowMan::CreateWindow(den::DEN_Window &wInfo, den::DEN_Context &cInfo) {
	// if vector has size 0, SDL hasn't been initialized yet
	this->InitSDL();
	Uint32 win_flags = this->SetWindowAttribs(wInfo, cInfo);
	
	// creating window
	SDL_Window* win = SDL_CreateWindow(wInfo.name.c_str(),
									   wInfo.pos_x, wInfo.pos_y,
									   wInfo.width, wInfo.height,
									   win_flags);
	
	// checking for errors
	if (win == nullptr) {
		std::cerr << "[ERROR] Could not create Window '" << wInfo.name <<
		"':" << SDL_GetError() << std::endl;
		exit(EXIT_FAILURE);
	}
	else {
		SDL_GLContext cont = SDL_GL_CreateContext(win);
		if (cont == NULL) {
			std::cerr << "[ERROR] Could not create context for '" << wInfo.name <<
			"':" << SDL_GetError() << std::endl;
			exit(EXIT_FAILURE);
		}
		else {
			this->window = win;
			this->context = cont;
			
#if not defined __APPLE__
			glewExperimental = GL_TRUE;
			GLenum gErr = glewInit();
			if (gErr != GLEW_OK) {
				std::cerr << "ERROR: Could not initialize GLEW!\n" << glewGetErrorString(gErr);
			}
#endif
		}
	}
	
}


GLvoid den::WindowMan::InitSDL() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cerr << "ERROR: Could not initialize SDL_VIDEO!\n" << SDL_GetError();
		exit(EXIT_FAILURE);
	}
	else {
		GLint flags = IMG_INIT_PNG | IMG_INIT_JPG;
		if (!(IMG_Init(flags) & flags)) {
			std::cerr << "ERROR: SDL_image could not initialize!\n" << IMG_GetError();
			exit(EXIT_FAILURE);
		}
	}
}




