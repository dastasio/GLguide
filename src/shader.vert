R"SHADER(
#version 330 core

layout( location = 0) in vec2 position;
layout( location = 1) in vec2 textureCoordinates;
layout( location = 2) in vec3 in_color;

out vec2 texCoords;
out vec3 vertex_color;
void main() {
	gl_Position = vec4( position.x, -position.y, 0.0, 1.0);
	texCoords = textureCoordinates;
	vertex_color = in_color;
}
)SHADER"