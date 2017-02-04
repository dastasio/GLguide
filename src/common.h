#ifndef COMMON_H
#define COMMON_H
#define BUFFER_OFFSET(bytes)  (( GLvoid*) (bytes))
#define ARRAY_SIZE(arr)  ( sizeof(arr)/sizeof(arr[0]))
#include "global.h"

GLuint modelShader();
GLuint lightShader();

#endif // COMMON_H
