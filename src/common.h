#ifndef COMMON_H
#define COMMON_H
#define BUFFER_OFFSET(bytes)  (( GLvoid*) (bytes))
#include "global.h"

static char* readShaderSource( const char* shaderFile);
GLuint InitShader( const char* vShaderFile, const char* fShaderFile);

#endif // COMMON_H
