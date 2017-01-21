#pragma once

// including external libraries
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#define GLEW_STATIC
#include <GL/glew.h>

#ifdef _WIN32
#define SDL_MAIN_HANDLED
#endif
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_opengl.h>


// glm library
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"


// including personal library
#include "common.h"
#include "cube.h"
#include "textures.h"
#include "dav_sdl.h"