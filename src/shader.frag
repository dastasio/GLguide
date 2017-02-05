R"SHADER(
#version 330 core

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	float shineFactor;
};

struct Light {
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec2 texCoordinates;
in vec3 normal;
in vec3 fragPos;
out vec4 final_color;

uniform Material mater;
uniform Light light;
uniform vec3 objColor;
uniform vec3 viewPos;

void main() {
	// Ambient
	vec3 ambient = light.ambient * vec3( texture(mater.diffuse, texCoordinates));

	// Diffuse
	vec3 norm = normalize(normal);
	vec3 lDir = normalize( light.position - fragPos);
	float diff = max(dot(norm, lDir), 0.0);
	vec3 diffuse = light.diffuse * diff * vec3(texture(mater.diffuse, texCoordinates));

	// Specular
	vec3 vDir = normalize( viewPos - fragPos);
	vec3 refDir = reflect( -lDir, norm);
	float spec = pow( max(dot(vDir, refDir), 0.0), mater.shineFactor);
	vec3 specular = light.specular * spec * vec3(texture(mater.specular, texCoordinates));

	vec3 result = ambient + diffuse + specular;
	final_color = vec4( result, 1.0);
}
)SHADER"
