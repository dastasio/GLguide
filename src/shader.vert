R"SHADER(
#version 330 core

layout( location = 0) in vec3 position;
layout( location = 1) in vec2 textureCoordinates;

// uniform transformation matrix
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 texCoords;
void main() {
	gl_Position = /*projection * view * model * */vec4( position.xyz, 1.0);
	texCoords = textureCoordinates;
}
)SHADER"