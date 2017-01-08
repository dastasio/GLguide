R"SHADER(
#version 330 core

in vec2 texCoords;
in vec3 vertex_color;
out vec4 final_color;

uniform sampler2D finalTexture;

void main() {
	final_color = texture( finalTexture, texCoords) * vec4(vertex_color, 1.0);
}
)SHADER"