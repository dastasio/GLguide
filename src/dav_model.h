#pragma once
#include "global.h"
#include "dav_mesh.h"
#include "textures.h"
#include "structs.h"

using namespace std;

class Model {
public:
	Model(const GLchar* path) {
		this->loadModel(path);
	}
	
	GLvoid Draw(GLuint program);
private:
	// model data
	vector<Mesh> meshes;
	string directory;
	
	// functions
	GLvoid loadModel(string path);
	GLvoid processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	vector<Texture> loadMaterialTexture(aiMaterial* mat, aiTextureType type, string typeName);
	
	vector<Texture> textures_loaded;
};
