#include "dav_mesh.h"


/* Mesh constructor */
Mesh::Mesh( vector<Vertex> v, vector<GLuint> inds, vector<Texture> tex) {
	this->verts = v;
	this->indices = inds;
	this->textures = tex;
	
	this->setupMesh();
}


GLvoid Mesh::setupMesh() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(Vertex), verts.data(), GL_STATIC_DRAW);
	
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
	
	// positions
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(0));
	glEnableVertexAttribArray(0);
	// normals
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(offsetof(Vertex, norm)));
	glEnableVertexAttribArray(1);
	// texture coordinates
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(offsetof(Vertex, tex)));
	glEnableVertexAttribArray(2);
	
	
	glBindVertexArray(0);
}

GLvoid Mesh::Draw(GLuint program) {
	GLuint diffuseNum = 1;
	GLuint specularNum = 1;
	
	for( GLint i = 0; i < textures.size(); ++i) {
		
		glActiveTexture( GL_TEXTURE0 + i);
		
		std::ostringstream num;
		string name = textures[i].type;
		if( name == "texture_diffuse")
			num << diffuseNum++;
		else if( name == "texture_specular")
			num << specularNum++;
		
		name.append( num.str());
		glUniform1i( glGetUniformLocation( program, ("mater." + name).c_str()), i);
		glBindTexture(GL_TEXTURE_2D, textures[i].ID);
	}
	glActiveTexture(GL_TEXTURE0);
	
	// drawing
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

















