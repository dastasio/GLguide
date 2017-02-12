#pragma once
#include "global.h"
#include "structs.h"
using namespace std;

class davMesh {
public:
	vector<Vertex> verts;
	vector<GLuint> indices;
	vector<Texture> textures;
	
	davMesh(vector<Vertex> v, vector<GLuint> inds, vector<Texture> tex);
	GLvoid Draw(GLuint program);
private:
	GLuint VAO, VBO, EBO;
	
	GLvoid setupMesh();
};
