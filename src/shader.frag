R"SHADER(
#version 330 core

in vec3 normal;
in vec3 fragPos;
in vec3 ligPos;
out vec4 final_color;

uniform vec3 lightColor;
uniform vec3 objColor;
uniform vec3 viewPos;

void main() {

	vec3 norm = normalize(normal);
	vec3 lDir = normalize( ligPos - fragPos);
	float diffuse = max( dot( norm, lDir), 0.0);
	vec3 diff = diffuse * lightColor;

	float strengthAmbient = 0.1;
	vec3 amb = strengthAmbient * lightColor;

	float specStrength = 0.5;
	vec3 vDir = normalize( vec3(0.0) - fragPos);
	vec3 refDir = reflect( -lDir, norm);
	float spec = pow(max(dot(vDir, refDir), 0.0), 32);
	vec3 sp = specStrength * spec * lightColor;

	vec3 result = (amb + diff + sp) * objColor;
	final_color = vec4( result, 1.0);
}
)SHADER"
