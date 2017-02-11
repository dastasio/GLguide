R"SHADER(
#version 330 core
#define NUM_PLIGHTS 4

struct Material {
	sampler2D texture_diffuse0;
	sampler2D texture_diffuse1;
	sampler2D texture_diffuse2;
	sampler2D texture_diffuse3;
	sampler2D texture_specular0;
	sampler2D texture_specular1;
	sampler2D texture_specular2;
	sampler2D texture_specular3;
	float shineFactor;
};

struct DirLight {
	vec3 direction;

	vec3 amb;
	vec3 diff;
	vec3 spec;
};

struct PointLight {
	vec3 position;

	float constant;
	float linear;
	float quadratic;

	vec3 amb;
	vec3 diff;
	vec3 spec;
};


in vec2 texCoordinates;
in vec3 normal;
in vec3 fragPos;
out vec4 final_color;

uniform Material mater;
uniform DirLight dirL;
uniform PointLight pointL[NUM_PLIGHTS];
uniform vec3 viewPos;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 frag, vec3 viewDir);

void main() {
/*
	vec3 N = normalize(normal);
	vec3 vDir = normalize(viewPos - fragPos);

	// Phase 1: directional light
	vec3 result = CalcDirLight(dirL, N, vDir);
	// Phase 2: point lights
	for( int i = 0; i < NUM_PLIGHTS; ++i) {
		result += CalcPointLight( pointL[i], N, fragPos, vDir);
	}
	// Phase3: spotlight
*/
	vec3 result = vec3(texture(mater.texture_diffuse0, texCoordinates));

	final_color = vec4(result, 1.0);
}

/*
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir) {
	vec3 lDir = normalize(-light.direction);

	// Diffuse
	float diffIntensity = max(dot(normal, lDir), 0.0);
	// Specular
	vec3 refLight = reflect( -lDir, normal);
	float specIntensity = pow( max( dot(viewDir, refLight), 0.0), mater.shineFactor);

	// results
	vec3 ambient = light.amb * vec3( texture(mater.diffuse, texCoordinates));
	vec3 diffuse = light.diff * diffIntensity  * vec3( texture(mater.diffuse, texCoordinates));
	vec3 specular = light.spec * specIntensity * vec3( texture( mater.specular, texCoordinates));
	return ( ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 frag, vec3 viewDir) {
	vec3 lDir = normalize( light.position - frag);
	// Diffuse
	float diffIntensity = max( dot( normal, lDir), 0.0);
	// Specular
	vec3 refLight = reflect( -lDir, normal);
	float specIntensity = pow(max( dot( viewDir, refLight), 0.0), mater.shineFactor);
	// Attenuation
	float dist = length(light.position - frag);
	float atten = 1.0 / ( light.constant + light.linear * dist + light.quadratic * ( dist * dist));

	// Results
	vec3 ambient = light.amb * vec3( texture(mater.diffuse, texCoordinates));
	vec3 diffuse = light.diff * diffIntensity * vec3( texture(mater.diffuse, texCoordinates));
	vec3 specular = light.spec * specIntensity * vec3( texture(mater.specular, texCoordinates));
	ambient  *= atten;
	diffuse  *= atten;
	specular *= atten;
	return ( ambient + diffuse + specular);
}
*/

)SHADER"























