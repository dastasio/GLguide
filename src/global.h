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
#include "glm/gtx/rotate_vector.hpp"


// including personal library
#include "common.h"
#include "app.h"
#include "textures.h"
#include "dav_sdl.h"
#include "camera.h"
#include "objs.h"
