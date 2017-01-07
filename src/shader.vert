R"SHADER(
#version 330 core

layout( location = 0) in vec3 position;
out vec3 vertex_Position;

void main() {
	gl_Position = vec4( position.xyz, 1.0);
	vertex_Position = vec3(position.xyz);
}
)SHADER"