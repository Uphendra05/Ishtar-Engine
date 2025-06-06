#version 330 core

out vec4 FragColor;

in vec2 TexCoords;

// G-buffer textures
uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedoSpec;

struct Light 
{
    vec3 position;
    vec4 color;
    float linear;
    float quadratic;
};

#define MAX_LIGHTS 32
uniform Light lights[MAX_LIGHTS];
uniform int lightCount = 1;

uniform vec3 viewPos;

void main()
{
    vec3 FragPos = texture(gPosition, TexCoords).rgb;
    vec3 Normal = normalize(texture(gNormal, TexCoords).rgb);
    vec3 Albedo = texture(gAlbedoSpec, TexCoords).rgb;
    float SpecularStrength = texture(gAlbedoSpec, TexCoords).a;

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 result = vec3(0.0);

    for (int i = 0; i < lightCount; ++i)
    {
        // Light direction
        vec3 lightDir = normalize(lights[i].position - FragPos);

        // Diffuse
        float diff = max(dot(Normal, lightDir), 0.0);
        vec3 diffuse = diff * Albedo * lights[i].color.rgb;

        // Specular
        vec3 reflectDir = reflect(-lightDir, Normal);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 10.0); // hardcoded shininess
        vec3 specular = SpecularStrength * spec * lights[i].color.rgb;

        // Attenuation
        float distance = length(lights[i].position - FragPos);
        float attenuation = 1.0 / (1.0 + lights[i].linear * distance + lights[i].quadratic * (distance * distance));

        result += (diffuse + specular) * attenuation;
    }

    FragColor = vec4(result, 1.0);
}