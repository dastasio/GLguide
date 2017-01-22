R"SHADER(
#version 330 core

in vec2 texCoords;
out vec4 final_color;

uniform sampler2D texSmile;
uniform sampler2D texContainer;

void main() {
	vec2 Coordinates = vec2( texCoords.x, 1 - texCoords.y);
	final_color = mix( texture( texContainer, Coordinates), texture( texSmile, Coordinates), 0.2);
}
)SHADER"