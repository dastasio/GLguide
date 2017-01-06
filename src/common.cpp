#include "common.h"

#define VSHADER "shader.vert"
#define FSHADER "shader.frag"
#define FSHADER2 "shader2.frag"

// create GLSL program object from vertex and fragment shaders
void InitShader( ) {
	// reading shader sources
		const GLchar* vertexSource =
		#include VSHADER
			;
		const GLchar* fragmentSource =
		#include FSHADER
			;
		const GLchar* fragmentSource2 =
		#include FSHADER2
			;
		if (vertexSource == NULL) {
			std::cout << "FAILED TO READ " << VSHADER << std::endl;
			exit(EXIT_FAILURE);
		}
		if (fragmentSource == NULL) {
			std::cout << "FAILED TO READ " << FSHADER << std::endl;
			exit(EXIT_FAILURE);
		}
		if (fragmentSource2 == NULL) {
			std::cout << "FAILED TO READ " << FSHADER2 << std::endl;
			exit(EXIT_FAILURE);
		}
	// read shader sources

	// success flag for shaders compilation
	GLint success;

	// creating vertShader and fragShader objects
		// creating vertex shader
		GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);

		// attaching source code to vertex shader object
		glShaderSource(vertShader, 1, &vertexSource, NULL);

		// compiling vertex shader
		glCompileShader(vertShader);

		// checking for successful compilation (VERTEX)
		GLchar infoLog[512];
		glGetShaderiv(vertShader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(vertShader, 512, NULL, infoLog);
			std::cout << "FAILED TO COMPILE VERTEX SHADER!\n" << infoLog << std::endl;
			exit(EXIT_FAILURE);
		}



		// creating fragment shader
		GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragShader, 1, &fragmentSource, NULL);
		glCompileShader(fragShader);

		// checking for successful compilation (FRAGMENT)
		glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(fragShader, 512, NULL, infoLog);
			std::cout << "FAILED TO COMPILE FRAGMENT SHADER!\n" << infoLog << std::endl;
			exit(EXIT_FAILURE);
		}

		// creating second fragment shader
		GLuint fragShader2 = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragShader2, 1, &fragmentSource2, NULL);
		glCompileShader(fragShader2);

		// checking successful
		glGetShaderiv(fragShader2, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(fragShader2, 512, NULL, infoLog);
			std::cout << "FAILED TO COMPILE FRAGMENT SHADER 2!\n" << infoLog << std::endl;
			exit(EXIT_FAILURE);
		}
	// created vertShader and fragShader objects

	// creating shader program
	GLuint program, program2;
	program = glCreateProgram();

	// linking shaders
	glAttachShader(program, vertShader);
	glAttachShader(program, fragShader);
	glLinkProgram(program);

	// checking for successful linking
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cout << "FAILED TO LINK SHADER PROGRAM:\n" << infoLog << std::endl;
		exit(EXIT_FAILURE);
	}

	program2 = glCreateProgram();
	glAttachShader(program2, vertShader);
	glAttachShader(program2, fragShader2);
	glLinkProgram(program2);

	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program2, 512, NULL, infoLog);
		std::cout << "FAILED TO LINK SHADER PROGRAM2:\n" << infoLog << std::endl;
		exit(EXIT_FAILURE);
	}

	// deleting shaders
	glDeleteShader(vertShader);
	glDeleteShader(fragShader);
	glDeleteShader(fragShader2);
	
	gProgram[0] = program;
	gProgram[1] = program2;
}
