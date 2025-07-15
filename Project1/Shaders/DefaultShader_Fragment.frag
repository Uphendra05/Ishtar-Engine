#version 330 core

out vec4 FragColor;

struct Material 
{
   // vec3 ambient;
    
    vec4 baseColor;
	vec4 ambientColor;
	float specularValue;
    float shininess;
    float alpha;
   
}; 

uniform sampler2D diffuse_Texture;
uniform  sampler2D specular_Texture;  
uniform sampler2D opacity_Texture;
uniform sampler2D normal_Texture;
uniform sampler2D displacement_Texture;
uniform sampler2D shadowMap;

struct sLight
{
    vec3 position;			
	//vec4 diffuse;	// Colour of the light (used for diffuse)
	//vec4 specular;	// rgb = highlight colour, w = power
		
	vec3 direction;	// Spot, directional lights
	int lightType;	// x = lightType, y = inner angle, z = outer angle, w = TBD
	        
                   // 0 = pointlight
    float constant;
    float linear;
    float quadratic;	
    
    // 1 = spot light
					// 2 = directional light
    vec4 ambient;

     float cutOff;
    float outerCutOff;
    vec4 color;
    
};


in vec3 FragPosition;  
in vec2 TextureCoordinates;
in vec4 meshColour;
in vec4 FragPosLightSpace;
in mat3 TBN;

uniform vec3 viewPos;
uniform Material material;
uniform bool isMasking;
uniform bool isCutout;

uniform int DIRECTION_LIGHT_ID =0;
uniform int POINT_LIGHT_ID =1;
uniform int SPOTLIGHT_ID =2;
const int LIGHTCOUNT = 15;
uniform sLight lights[LIGHTCOUNT];

uniform int ShaderBlend;
uniform bool ObjectBlend;
uniform float alphaCutOffThreshold;

float temp;

vec4 CalculateLight(vec3 norm, vec3 viewDir,float shadowCalc );
float near = 0.1; 
float far  = 100.0; 

float LinearizeDepth(float depth) 
{
    float z = depth * 2.0 - 1.0; // back to NDC 
    return (2.0 * near * far) / (far + near - z * (far - near));	
}

uniform bool isDepthBuffer;
uniform samplerCube skybox;

uniform float biasValue;
uniform vec3 lightDir;
float ShadowCalculation(vec4 fragPosLightSpace, vec3 normal);

//Fog
uniform float fogDensity;
uniform float fogStart;
uniform float fogEnd;
uniform vec3 fogColor;
uniform bool fogActive;

float CalcFog();
float CalcLinearFog();
float CalcExpoFog();


//Toon Shader
const int shadingLevels = 4;
const float scaleFactor = 1.0/ shadingLevels;
uniform bool isCellShading = false;

void main()
{    
    // properties
    vec3 normalTex = texture(normal_Texture, TextureCoordinates).rgb;
    vec3 displacementTex = texture(displacement_Texture, TextureCoordinates).rgb;
    vec3 normal = normalize(normalTex * 2.0 - 1.0); // tangent space normal
    vec3 finalnorm = normalize(TBN * normal); 


    vec3 viewDirWorld = normalize(viewPos - FragPosition);
    vec3 viewDir = normalize(TBN * viewDirWorld);

    vec3 R = reflect(-viewDir, finalnorm);

    float shadow =  ShadowCalculation(FragPosLightSpace, finalnorm);

    vec4 result = CalculateLight(finalnorm,viewDir,shadow);
  
     vec4 cutOff = texture(diffuse_Texture, TextureCoordinates);
 
     //float maskSample = texture(material.alphaMask, TextureCoordinates).r;

     //vec4 finalColor = vec4(result, isCutout ? 1.0f : maskSample);
     

     if(ShaderBlend ==1)
     {
       result.w = 1.0;
     }
     else if(ShaderBlend == 3)
     {
        if(result.w <alphaCutOffThreshold)
        {
         discard;
        }
     }
    

//      if (isCutout)
//     {
//      
//         if (cutOff.a < 0.1)
//        {
//            discard;
//        }
//        FragColor = result*cutOff.a; 
//     
//     }



     

     if(isDepthBuffer)
     {

          float depth = LinearizeDepth(gl_FragCoord.z) / far;
          vec4 depthVec4 = vec4(vec3(pow(depth, 1.4)), 7.0);
          FragColor = (result)* (1 - depthVec4) + depthVec4;
      }
      else
      {
            if(fogColor != vec3(0) && fogActive)
             {
               float fogFactor = CalcExpoFog();
               result = mix(vec4(fogColor,1.0),result,fogFactor);

             }
             FragColor = result;


      }


     

    //FragColor = vec4( temp,temp, temp,1.0);
     
    

}

float CalcLinearFog()
{

   float camDist = length(FragPosition - viewPos);
   float fogRange = fogEnd - fogStart;
   float fogDist = fogEnd - camDist;
   float fogFactor = fogDist /fogRange;
   fogFactor  = clamp(fogFactor,0.0,1.0);
   return fogFactor;

}

float CalcExpoFog()
{
   float camDist = length(FragPosition - viewPos);
   float distRatio = 4.0 * camDist / fogEnd;
   float fogFactor = exp(-distRatio * fogDensity * distRatio * fogDensity);

   return fogFactor;
 
}

float CalcFog()
{

  float fogFac = 1;

  if(fogStart >= 0)
  {
    fogFac = CalcLinearFog();
  }
  else
  {
     fogFac = CalcExpoFog();
  
  }


  return fogFac;
}


float ShadowCalculation(vec4 fragPosLightSpace, vec3 normal)
{

   // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(shadowMap, projCoords.xy).r; 
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // calculate bias (based on depth map resolution and slope)
    vec3 lightDir = normalize(lights[0].position - FragPosition);
    float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);



    // check whether current frag pos is in shadow
    // float shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0;
    // PCF
    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r; 
            shadow += currentDepth - bias > pcfDepth  ? 1.0 : 0.0;        
        }    
    }
    shadow /= 9.0;
    
    // keep the shadow at 0.0 when outside the far_plane region of the light's frustum.
    if(projCoords.z > 1.0)
        shadow = 0.0;
        
    return shadow;
}

  


vec4 CalculateLight(vec3 norm, vec3 viewDir,float shadowCalc)
{

    vec4 result = vec4(0,0,0,0);
  
    vec4 diffuseColor = texture(diffuse_Texture, TextureCoordinates);

    vec4 textureColor = diffuseColor * meshColour * material.baseColor;

    for( int index = 0; index < LIGHTCOUNT; index++)
    {


       int LightType = lights[index].lightType;

       vec4 ambientColor = lights[index].ambient * material.ambientColor;
		ambientColor *= textureColor;

        

       if(LightType == DIRECTION_LIGHT_ID)
       {
         // Light direction (negative if it's the direction light is pointing toward)
         vec3 lightDir =  normalize(-lights[index].direction);
         
         // Diffuse shading
         float diff = max(dot(lightDir, norm), 0.0);
         
         if (isCellShading) 
         {
             diff = ceil(diff * shadingLevels) * scaleFactor;
         }
         
         vec3 diffuse = diff * lights[index].color.rgb * textureColor.rgb;
         
         // Specular shading
         vec3 reflectDir = reflect(-lightDir, norm);
         float spec = pow(max(dot(reflectDir, viewDir), 0.0), material.shininess);
         
         vec3 specular = vec3(0.0);
         if (!isCellShading && spec > 0.0) {
             float specMap = texture(specular_Texture, TextureCoordinates).r;
             specular = spec * material.specularValue * lights[index].color.rgb * specMap;
         }
         
         // Combine final color
         vec3 lighting = ambientColor.rgb + (1.0 - shadowCalc) * (diffuse + specular);
         vec4 finalColor = vec4(lighting, lights[index].color.a);
         
         // Accumulate
         result += finalColor;

        
       }
       if(LightType ==POINT_LIGHT_ID)
       {
     
        // Light vector
      
        vec3 lightDir =  normalize(lights[index].position - FragPosition);
        float distance = length(lights[index].position - FragPosition);
        
        // Attenuation
        float attenuation = 1.0 / (lights[index].constant + lights[index].linear * distance + lights[index].quadratic * (distance * distance));
        
        // Ambient
        vec3 ambient = ambientColor.rgb * attenuation;
        
        // Diffuse
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * lights[index].color.rgb * textureColor.rgb * attenuation;
        
        // Specular
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(reflectDir, viewDir), 0.0), material.shininess);
        float specMap = texture(specular_Texture, TextureCoordinates).r;
        vec3 specular = spec * material.specularValue * lights[index].color.rgb * specMap;
        
        // Combine
        vec3 finalColor = ambient + diffuse + specular;
        result += vec4(finalColor, 1.0);



       }

       if(LightType == SPOTLIGHT_ID)
       {
          // Light direction and distance
          vec3 lightDir =   normalize(lights[index].position - FragPosition);
          float distance = length(lights[index].position - FragPosition);
          
          // Attenuation (point light falloff)
          float attenuation = 1.0 / (lights[index].constant + 
                                     lights[index].linear * distance + 
                                     lights[index].quadratic * (distance * distance));
          
          // Spotlight intensity
          float theta = dot(lightDir, normalize(-lights[index].direction));
          float epsilon = lights[index].cutOff - lights[index].outerCutOff;
          float intensity = clamp((theta - lights[index].outerCutOff) / epsilon, 0.0, 1.0);
          
          // Ambient
          vec3 ambient = ambientColor.rgb * attenuation * intensity;
          
          // Diffuse
          float diff = max(dot(norm, lightDir), 0.0);
          vec3 diffuse = diff * lights[index].color.rgb * textureColor.rgb * attenuation * intensity;
          
          // Specular
          vec3 reflectDir = reflect(-lightDir, norm);
          float spec = pow(max(dot(reflectDir, viewDir), 0.0), material.shininess);
          float specMap = texture(specular_Texture, TextureCoordinates).r;
          vec3 specular = spec * material.specularValue * lights[index].color.rgb * specMap * attenuation * intensity;
          
          // Combine all
          vec3 finalColor = ambient + diffuse + specular;
          result += vec4(finalColor, 1.0);
       }

    }
     if (ObjectBlend)
     {
    // temp = texture(alphaMask, TextureCoordinates).r;
       result.w = texture(opacity_Texture, TextureCoordinates).r;
     
     }
     else
     {
        result.w =  material.baseColor.w;
     }
    
      return result;
}