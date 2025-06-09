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
    vec3 direction;
    int lightType;

    float constant;
    float linear;
    float quadratic;

    float cutOff;
    float outerCutOff;

    vec4 color;
    float radius;
};

#define MAX_LIGHTS 200
uniform Light lights[MAX_LIGHTS];

uniform vec3 viewPos;

int POINT_LIGHT_ID = 1;
int SPOTLIGHT_ID = 2;

 int lightCount = 200;



vec3 CalculateDeferredLighting( vec3 viewDir, vec3 fragPosition);

void main()
{
    vec3 FragPos = texture(gPosition, TexCoords).rgb;

    vec3 viewDir = normalize(viewPos - FragPos);

    vec3 result = CalculateDeferredLighting(viewDir, FragPos);

    FragColor = vec4(result, 1.0);
}

vec3 CalculateDeferredLighting( vec3 viewDir, vec3 fragPosition)
{
    vec3 result = vec3(0,0,0);


    vec3 Normal = normalize(texture(gNormal, TexCoords).rgb);
    vec3 Albedo = texture(gAlbedoSpec, TexCoords).rgb;
    float SpecularStrength = texture(gAlbedoSpec, TexCoords).a;


    for (int i = 0; i < lightCount; ++i)
    {
        float lightDistance = length(lights[i].position - fragPosition);
        if(lightDistance < lights[i].radius)
        {
           
        



                int LightType = lights[i].lightType;
                
                if(LightType == POINT_LIGHT_ID)
                {
                
                 // Light direction
                 vec3 lightDir = normalize(lights[i].position - fragPosition);
                
                 // Diffuse
                 float diff = max(dot(Normal, lightDir), 0.0);
                 vec3 diffuse = diff * Albedo * lights[i].color.rgb;
                
                 // Specular
                 vec3 reflectDir = reflect(-lightDir, Normal);
                 float spec = pow(max(dot(viewDir, reflectDir), 0.0), 300.0); // hardcoded shininess
                 vec3 specular = SpecularStrength * spec * lights[i].color.rgb;
                
                 // Attenuation
                 float attDistance = length(lights[i].position - fragPosition);
                 float attenuation = 1.0 / (lights[i].constant + lights[i].linear * attDistance + lights[i].quadratic * (attDistance * attDistance));
                
                  result += (diffuse + specular) * attenuation;
                }
                
                if(LightType == SPOTLIGHT_ID)
                {
                
                  vec3 lightDir = normalize(lights[i].position - fragPosition);
                  float theta = dot(lightDir, normalize(-lights[i].direction)); // angle between light dir and fragment-to-light dir
                
                  float epsilon = lights[i].cutOff - lights[i].outerCutOff;
                  float intensity = clamp((theta - lights[i].outerCutOff) / epsilon, 0.0, 1.0);
                  
                  // Diffuse
                  float diff = max(dot(Normal, lightDir), 0.0);
                  vec3 diffuse = diff * Albedo * lights[i].color.rgb;
                  
                  // Specular
                  vec3 reflectDir = reflect(-lightDir, Normal);
                  float spec = pow(max(dot(viewDir, reflectDir), 0.0), 300.0); // shininess
                  vec3 specular = SpecularStrength * spec * lights[i].color.rgb;
                  
                  // Attenuation
                  float attDistance2 = length(lights[i].position - fragPosition);
                  float attenuation = 1.0 / (lights[i].constant  + lights[i].linear * attDistance2 + lights[i].quadratic * (attDistance2 * attDistance2));
                  
                  // Apply spotlight intensity and attenuation
                  diffuse *= intensity;
                  specular *= intensity;
                  
                   result += (diffuse + specular) * attenuation;
                
                
                
                
                }
  
     }
    
    }

    return result;

}