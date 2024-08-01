#version 330 core

struct Material
{
	vec4 baseColor;
};


in vec2 TexCoord;
out vec4 fragColor;

uniform Material material;
uniform sampler2D diffuseTexture;

void main()
{
	vec4 diffuse = texture(diffuseTexture, TexCoord);
	diffuse.a *= material.baseColor.w;
	vec4 result = diffuse * material.baseColor;
	 if(diffuse.a < 0.1)
        discard;
    fragColor = vec4(result);
} 