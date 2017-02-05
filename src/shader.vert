R"SHADER(
#version 330 core

layout( location = 0) in vec3 position;
layout( location = 1) in vec3 N;
layout( location = 2) in vec2 coords;
out vec3 normal;
out vec3 fragPos;
out vec2 texCoordinates;

// uniform transformation matrix
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
	gl_Position = projection * view * model * vec4( position.xyz, 1.0);
	fragPos = vec3(model * vec4(position, 1.0));

	normal = mat3(transpose(inverse(model))) * N;
	texCoordinates = coords;
}
)SHADER"