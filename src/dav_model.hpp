#pragma once
#include "global.h"
#include "dav_mesh.hpp"

using namespace std;

class davModel {
public:
	davModel(const GLchar* path) {
		this->loadModel(path);
	}
	
	GLvoid Draw(GLuint program);
private:
	// model data
	vector<davMesh> meshes;
	string directory;
	
	// functions
	GLvoid loadModel(string path);
	GLvoid processNode(aiNode* node, const aiScene* scene);
	davMesh processMesh(aiMesh* mesh, const aiScene* scene);
	vector<Texture> loadMaterialTexture(aiMaterial* mat, aiTextureType type, string typeName);
	
	vector<Texture> textures_loaded;
};
