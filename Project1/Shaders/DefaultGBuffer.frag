#version 330 core
layout (location = 0) out vec3 gPosition;
layout (location = 1) out vec3 gNormal;
layout (location = 2) out vec4 gAlbedoSpec;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform sampler2D diffuse_Texture;
uniform sampler2D specular_Texture;
uniform float specularIntensity ;


void main()
{
    gPosition = FragPos;
    gNormal = normalize(Normal);
    vec3 texColor = texture(diffuse_Texture, TexCoords).rgb;
    float specColor = texture(specular_Texture, TexCoords).r ;

    gAlbedoSpec.rgb = texColor; // Red + texture mix   
    gAlbedoSpec.a = specColor * specularIntensity;
}