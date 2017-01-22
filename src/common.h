#ifndef COMMON_H
#define COMMON_H
#define BUFFER_OFFSET(bytes)  (( GLvoid*) (bytes))
#define ARRAY_SIZE(arr)  ( sizeof(arr)/sizeof(arr[0]))
#include "global.h"

GLuint InitShader();
std::vector<GLfloat> toVec5(glm::vec3 v3[], glm::vec2 v2[]);

#endif // COMMON_H
