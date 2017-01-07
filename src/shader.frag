R"SHADER(
#version 330 core

in vec3 vertex_Position;
out vec4 out_color;

void main() {
	out_color = vec4(vertex_Position.rgb, 1.0);
}
)SHADER"