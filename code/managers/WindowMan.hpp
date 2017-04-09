#pragma once
#include "global.h"
#include <vector>
#include <map>

namespace den {
	
	struct DEN_Window {
		GLuint pos_x, pos_y;
		GLuint width, height;
		GLboolean resizable, shown;
		std::string name;
		
		DEN_Window() {
			pos_x = 0;
			pos_y = 0;
			
			width = 1024;
			height = 720;
			name = "OpenGL window";
			resizable = GL_TRUE;
			shown = GL_TRUE;
		}
		
		DEN_Window(std::string name,
			   GLuint x, GLuint y,
			   GLuint w, GLuint h,
			   GLboolean resize = GL_TRUE, GLboolean show = GL_TRUE) {
			
			this->name = name;
			this->pos_x = x;
			this->pos_y = y;
			this->width = w;
			this->height = h;
			this->resizable = resize;
			this->shown = show;
		}
		
		DEN_Window(DEN_Window& win) {
			this->name = win.name;
			this->pos_x = win.pos_x;
			this->pos_y = win.pos_y;
			this->width = win.width;
			this->height = win.height;
			this->resizable = win.resizable;
			this->shown = win.shown;
		}
	};
	
	struct DEN_Context {
		GLuint v_major, v_minor;
		GLboolean core_profile;
		
		DEN_Context() {
			this->v_major = 3;
			this->v_minor = 3;
			this->core_profile = GL_TRUE;
		};
		
		DEN_Context(GLuint maj, GLuint min, GLboolean core = GL_TRUE) {
			this->v_major = maj;
			this->v_minor = min;
			this->core_profile = core;
		}
		
		DEN_Context(DEN_Context& con) {
			this->v_major = con.v_major;
			this->v_minor = con.v_minor;
			this->core_profile = con.core_profile;
		}
	};
	
	
	class WindowMan {
	public:
		WindowMan() {}
		~WindowMan() {
			//TODO
		}
		
		GLvoid CreateWindow(DEN_Window &wInfo, DEN_Context &cInfo);
		
		GLvoid Loop();
	private:
		SDL_Window* window;
		SDL_GLContext context;
		
		GLvoid render();
		
		GLvoid InitSDL();
		Uint32 SetWindowAttribs(DEN_Window &window, DEN_Context &context);
	};
}
