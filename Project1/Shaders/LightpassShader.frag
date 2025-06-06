#version 330 core

out vec4 FragColor;

in vec2 TexCoords;

// G-buffer textures
uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedoSpec;

struct Light {
    vec3 position;
    vec3 color;

    float linear;
    float quadratic;
};

uniform Light light;
uniform vec3 viewPos;

void main()
{
    // Sample G-buffer
    vec3 FragPos = texture(gPosition, TexCoords).rgb;
    vec3 Normal = normalize(texture(gNormal, TexCoords).rgb);
    vec3 Albedo = texture(gAlbedoSpec, TexCoords).rgb;
    float SpecularStrength = texture(gAlbedoSpec, TexCoords).a;

    // Lighting calculations
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(Normal, lightDir), 0.0);
    
    // Specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, Normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 20.0); // hardcoded shininess
    vec3 specular = SpecularStrength * spec * light.color;

    // Attenuation
    float distance = length(light.position - FragPos);
    float attenuation = 1.0 / (1.0 + light.linear * distance + light.quadratic * (distance * distance));

    vec3 lighting = (Albedo * diff + specular) * light.color * attenuation;

    FragColor = vec4(lighting , 1.0) ;
}