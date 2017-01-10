R"SHADER(
#version 330 core

in vec2 texCoords;
in vec3 vertex_color;
out vec4 final_color;

uniform sampler2D mTexture1;
uniform sampler2D mTexture2;

void main() {
	vec2 cords = vec2( 1 - texCoords.x, texCoords.y);
	final_color = mix( texture( mTexture1, -texCoords), texture( mTexture2, cords), 0.2);
}
)SHADER"