#include "ShaderMan.hpp"
#include <fstream>


/*
 ShaderMan's ReadShader func:
 - params:
	filename, string that contains path to shader source
 - returns: content of file
 - s.e.: quits app in case of errors
*/
string den::ShaderMan::ReadShader(const string &filename) {
	// reading source file
	string code;
	ifstream file(filename, ios::in);
	
	if(!file.good()) {
		cerr << "[ERROR] Can't read file " << filename << endl;
		exit(EXIT_FAILURE);
	}
	
	// getting source code length and resizing string accordingly
	file.seekg(0, ios::end);
	code.resize((unsigned int)file.tellg());
	// reading file content into string
	file.seekg(0, ios::beg);
	file.read(&code[0], code.size());
	file.close();
	return code;
}



/* ShaderMan's shader compiling func
 - params:
	type, type of shader to compile
	source, string containing source code of shader
	shaderName, string containing name with which to refer
				to the shader in case of compiling error
 - returns:
	GLuint, compiled shader
 - s.e.: quits application in case of errors
*/
GLuint den::ShaderMan::CompileShader(GLenum type,
									 const string &source,
									 const string &shaderName) {
	// success flag
	GLint success = 0;
	// creating new empty shader
	GLuint shader = glCreateShader(type);
	
	const GLchar* code_source = source.c_str();
	const GLint code_size = source.size();
	
	// attempting compilation
	glShaderSource(shader, 1, &code_source, &code_size);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	
	// if compilation is unsuccessful, report errors and exit
	if (success == GL_FALSE) {
		GLint log_size = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_size);
		GLchar* log = new GLchar[log_size];
		glGetShaderInfoLog(shader, log_size, NULL, &log[0]);
		cerr << "[ERROR] Compiling shader " << shaderName << ":\n" << log << endl;
		exit(EXIT_FAILURE);
	}
	
	// returning compiled shader
	return shader;
}



/* ShaderMan's new-program func
 - params:
	shaderName, name to use when adding program to map
	vertSourcePath, path where vertex shader is read
	fragSourcePath, path where fragment shader is read
 - s.e.:
	quits app if link is not successful,
 
*/
GLvoid den::ShaderMan::CreateProgram(const string &shaderName,
									 const string &vertSourcePath,
									 const string &fragSourcePath) {
	
	GLuint program;
	
	// reading source codes
	string vert_code = this->ReadShader(vertSourcePath);
	string frag_code = this->ReadShader(fragSourcePath);
	
	// compiling shaders
	GLuint vert_shader = CompileShader(GL_VERTEX_SHADER, vert_code, shaderName);
	GLuint frag_shader = CompileShader(GL_FRAGMENT_SHADER, frag_code, shaderName);
	
	// linking success flag
	GLint link_success = 0;
	
	// attempting program linking with shaders
	program = glCreateProgram();
	glAttachShader(program, vert_shader);
	glAttachShader(program, frag_shader);
	glLinkProgram(program);

	// if linking is not successful, report errors and exit
	glGetProgramiv(program, GL_LINK_STATUS, &link_success);
	if (link_success == GL_FALSE) {
		GLint log_size = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_size);
		GLchar* log = new GLchar[log_size];
		glGetProgramInfoLog(program, log_size, nullptr, &log[0]);
		cerr << "[ERROR] Linking program " << shaderName << ":\n" << log << endl;
		exit(EXIT_FAILURE);
	}
	
	// trying to add new program to map
	GLboolean insertion = this->programs.insert(make_pair(shaderName, program)).second;
	if (insertion == GL_FALSE) {
		cout << "[WARING] A program already exists with name '" << shaderName << "'." << endl;
	}
	
}






















