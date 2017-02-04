R"SHADER(
#version 330 core

out vec4 final_color;

uniform vec3 lightColor;
uniform vec3 objColor;

void main() {
	final_color = vec4( objColor * lightColor, 1.0);
}
)SHADER"
