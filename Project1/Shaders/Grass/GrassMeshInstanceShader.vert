#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec4 aColor;


 out vec3 FragPosition;
 out vec3 Normal;
 out vec2 TextureCoordinates;
 out vec4 meshColour;
 out vec2 gradient;

uniform mat4 view;
uniform mat4 projection;
uniform float time = 0;
uniform mat4 instanceModel[100];

uniform bool isScrollingTexture;
uniform vec2 windDirection;
uniform float windStrength;
uniform float windDensity;
uniform float grassHeight;
// function prototypes

vec2 unity_gradientNoise_dir(vec2 p) {
    p = mod(p, 289.0);
    vec2 i = floor(p);
    vec2 f = fract(p);

    // Smooth interpolation between gradient vectors
    vec2 u = f * f * (3.0 - 2.0 * f);

    // Random gradient vectors at the integer grid points
    vec2 ga = normalize(vec2(fract(1.0 + 34.0 * i.x) * 2.0 - 1.0, 
                              fract(1.0 + 34.0 * i.y) * 2.0 - 1.0));
    vec2 gb = normalize(vec2(fract(1.0 + 34.0 * (i.x + 1.0)) * 2.0 - 1.0, 
                              fract(1.0 + 34.0 * (i.y + 1.0)) * 2.0 - 1.0));

    // Interpolate along x-axis
    vec2 va = mix(ga, gb, u.x);

    // Interpolate along y-axis
    return mix(va, gb, u.y);
}

float unity_gradientNoise(vec2 p) {
    vec2 ip = floor(p);
    vec2 fp = fract(p);
    float d00 = dot(unity_gradientNoise_dir(ip), fp);
    float d01 = dot(unity_gradientNoise_dir(ip + vec2(0, 1)), fp - vec2(0, 1));
    float d10 = dot(unity_gradientNoise_dir(ip + vec2(1, 0)), fp - vec2(1, 0));
    float d11 = dot(unity_gradientNoise_dir(ip + vec2(1, 1)), fp - vec2(1, 1));
    fp = fp * fp * fp * (fp * (fp * 6.0 - 15.0) + 10.0);
    return mix(mix(d00, d01, fp.y), mix(d10, d11, fp.y), fp.x);
}

void Unity_GradientNoise_float(vec2 UV, float Scale, out float Out) {
    Out = unity_gradientNoise(UV * Scale) + 0.5;
}


void Unity_TilingAndOffset_float(vec2 UV, vec2 Tiling, vec2 Offset, out vec2 Out)
{
    Out = UV * Tiling + Offset;
}

vec2 ApplyTilingAndOffset(vec2 uv, vec2 tiling, vec2 offset) 
{
  
    uv *= tiling;
    
   
    uv += offset;

    return uv;
}



void main()
{

   
     mat4 instanceModelID = instanceModel[gl_InstanceID]; 

   
    

	vec2 windSide = time *  windDirection ;

    vec2 outValue;

    Unity_TilingAndOffset_float(vec2(aTexCoords),vec2(1,1),windSide,outValue);

      //outValue =  vec2(aPos) ;
     // outValue+=time;
      //outValue+=windSide;

     float outGradient =  unity_gradientNoise(outValue * windDensity) + 0.5f;

      outGradient-= 0.5f;

      outGradient *=   windStrength;

      gradient =  vec2(aTexCoords.x,   1-aTexCoords.y);



      vec3 currentPosition = aPos;
        {
         currentPosition.x += outGradient ;
        }
      vec3 combinedValue = currentPosition;



      vec3 lerpedValue = mix(aPos, currentPosition,gradient.y );



     vec3 finalPosition =  lerpedValue;

     vec3 instancedPos = vec3(instanceModelID * vec4(finalPosition, 1.0));

      Normal =  mat3(transpose(inverse(instanceModelID))) * aNormal;

	 meshColour = aColor;

    // TextureCoordinates = aTexCoords;
     TextureCoordinates = aTexCoords;


     FragPosition = instancedPos;

	  gl_Position = projection * view * vec4(instancedPos, 1.0);
}



//void main()
//{
//    mat4 instanceModelID = instanceModel[gl_InstanceID]; 
//
//
//    vec2 windEffect = windDirection * windStrength * time;
//
//    vec3 currentPosition = aPos;
//
//    if (currentPosition.y > grassHeight)
//    {
//        currentPosition.x += unity_gradientNoise(vec2(aPos.xz) * windDensity + windEffect) * 0.1 * windStrength;
//    }
//
//    vec3 lerpedValue = mix(aPos, currentPosition, time);
//
//    vec3 finalPosition = lerpedValue;
//
//    vec3 instancedPos = vec3(instanceModelID * vec4(finalPosition, 1.0));
//
//    Normal = mat3(transpose(inverse(instanceModelID))) * aNormal;
//
//    meshColour = aColor;
//    TextureCoordinates = aTexCoords;
//    FragPosition = instancedPos;
//
//    gl_Position = projection * view * vec4(instancedPos, 1.0);
//}