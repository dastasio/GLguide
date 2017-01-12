R"SHADER(
#version 330 core

layout( location = 0) in vec2 position;
layout( location = 1) in vec2 textureCoordinates;
layout( location = 2) in vec3 in_color;

// uniform transformation matrix
uniform mat4 transform;

out vec2 texCoords;
out vec3 vertex_color;
void main() {
	vec4 final_pos = vec4( position.xy, 0.0, 1.0);
	gl_Position = transform * final_pos;
	texCoords = textureCoordinates;
	vertex_color = in_color;
}
)SHADER"