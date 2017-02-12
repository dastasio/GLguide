#include "dav_model.hpp"
#include "textures.h"

using namespace std;

/* Draw();
 - cycles through meshes in the model
 and calls their draw function
 */
GLvoid davModel::Draw(GLuint program) {
	for( GLint i = 0; i < meshes.size(); ++i) {
		meshes[i].Draw(program);
	}
}


/* loadModel();
 - loads model from given path and
 calls "processNode()" function
 */
GLvoid davModel::loadModel(string path) {
	Assimp::Importer imp;
	const aiScene* scene = imp.ReadFile(path.c_str(), aiProcess_Triangulate | aiProcess_FlipUVs);
	
	if( !scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		cout << "ERROR::ASSIMP::" << imp.GetErrorString() << endl;
		exit(EXIT_FAILURE);
	}
	directory = path.substr(0, path.find_last_of('/'));
	
	processNode(scene->mRootNode, scene);
}


/* processNode();
 - processes meshes of given node
 */
GLvoid davModel::processNode(aiNode *node, const aiScene *scene) {
	// process node meshes
	for( GLuint i = 0; i < node->mNumMeshes; ++i) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		this->meshes.push_back(processMesh(mesh, scene));
	}
	// do same for children
	for( GLuint i = 0; i < node->mNumChildren; ++i) {
		processNode(node->mChildren[i], scene);
	}
}


davMesh davModel::processMesh(aiMesh* mesh, const aiScene *scene) {
	vector<Vertex> vertices;
	vector<GLuint> indices;
	vector<Texture> textures;
	
	// vertices processing
	for(GLuint i = 0; i < mesh->mNumVertices; ++i) {
		Vertex v;
		// reading positions
		glm::vec3 position;
		position.x = mesh->mVertices[i].x;
		position.y = mesh->mVertices[i].y;
		position.z = mesh->mVertices[i].z;
		
		v.pos = position;
		
		// reading texture coordinates
		if(mesh->mTextureCoords[0]) {
			glm::vec2 vec;
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			v.tex = vec;
		}
		else
			v.tex = glm::vec2(0.0, 0.0);
		
		vertices.push_back(v);
	}
	// indices processing
	for(GLuint i = 0; i < mesh->mNumFaces; ++i) {
		aiFace face = mesh->mFaces[i];
		for(GLuint j = 0; j < face.mNumIndices; ++j)
			indices.push_back(face.mIndices[j]);
	}
	
	// material processing
	if(mesh->mMaterialIndex >= 0) {
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		vector<Texture> diffuseMaps = loadMaterialTexture(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		
		vector<Texture> specularMaps = loadMaterialTexture(material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}
	
	return davMesh(vertices, indices, textures);
}


vector<Texture> davModel::loadMaterialTexture(aiMaterial *mat, aiTextureType type, string typeName) {
	vector<Texture> texts;
	for(GLuint i = 0; i < mat->GetTextureCount(type); ++i) {
		aiString str;
		mat->GetTexture(type, i, &str);
		GLboolean skip = GL_FALSE;
		for(GLuint j = 0; j < textures_loaded.size(); ++i) {
			if(textures_loaded[j].path == str) {
				texts.push_back(textures_loaded[j]);
				skip = GL_TRUE;
				break;
			}
		}
		
		if( !skip) {
			Texture texture;
			string tmp = str.C_Str();
			texture.ID = loadTexture((this->directory + tmp).c_str());
			cout << (this->directory + tmp).c_str();
			texture.type = typeName;
			texture.path = str;
			texts.push_back(texture);
			this->textures_loaded.push_back(texture);
		}
	}
	return texts;
}
