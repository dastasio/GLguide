#include "global.h"
#include <map>
#include <string>

using namespace std;
namespace den {
	
	class ShaderMan {
	public:
		ShaderMan() {}
		~ShaderMan() {}
		
		GLvoid CreateProgram(const string& shaderName,
							 const string& vertSourcePath,
							 const string& fragSourcePath);
		
		const GLuint GetShader(const string& k) { return this->programs[k];}
		
	private:
		string ReadShader(const string& filename);
		
		GLuint CompileShader(GLenum type,
							 const string &source,
							 const string &shaderName);
		
		map<string, GLuint> programs;
	};
	
}
