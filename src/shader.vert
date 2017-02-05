R"SHADER(
#version 330 core

layout( location = 0) in vec3 position;
layout( location = 1) in vec3 N;
out vec3 normal;
out vec3 fragPos;
out vec3 ligPos;

// uniform transformation matrix
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 lightPos;

void main() {
	gl_Position = projection * view * model * vec4( position.xyz, 1.0);
	fragPos = vec3( view * model * vec4(position, 1.0));

	normal = mat3(transpose(inverse(view * model))) * N;
	ligPos = vec3(view * vec4(lightPos, 1.0));
}
)SHADER"