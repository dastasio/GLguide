#pragma once
#include "global.h"

void initTriangle( GLfloat, GLfloat);
void display();
void initTexture();
glm::mat4 transform(glm::vec3 t, GLfloat angl, glm::vec3 s);