#pragma once
#include "global.h"

using namespace glm;

struct Vertex {
	vec3 pos;
	vec3 norm;
	vec2 tex;
};

struct Texture {
	GLuint ID;
	std::string type;
	aiString path;
};
