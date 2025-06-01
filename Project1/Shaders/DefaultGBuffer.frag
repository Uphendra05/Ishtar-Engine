layout (location = 0) out vec3 gPosition;
layout (location = 1) out vec3 gNormal;
layout (location = 2) out vec4 gAlbedoSpec;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform sampler2D diffuse_Texture;
uniform float specularIntensity = 1.0;

void main()
{
    gPosition = FragPos;
    gNormal = normalize(Normal);
    vec3 texColor = texture(diffuse_Texture, TexCoords).rgb;
    gAlbedoSpec.rgb = mix(vec3(0, 0, 1), texColor, 0.5); // Red + texture mix   
    gAlbedoSpec.a = specularIntensity;
}