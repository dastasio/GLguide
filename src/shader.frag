R"SHADER(
#version 330 core

in vec3 normal;
in vec3 fragPos;
out vec4 final_color;

uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 objColor;

void main() {

	vec3 norm = normalize(normal);
	vec3 lDir = normalize( lightPos - fragPos);
	float diffuse = max( dot( norm, lDir), 0.0);
	vec3 diff = diffuse * lightColor;

	float strengthAmbient = 0.1;
	vec3 amb = strengthAmbient * lightColor;

	vec3 result = (amb + diff) * objColor;
	final_color = vec4( result, 1.0);
}
)SHADER"
