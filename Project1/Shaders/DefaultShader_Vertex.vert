#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec4 aColor;
layout (location = 6) in vec3 aTangent;
layout (location = 7) in vec3 aBiTangent;


 out vec3 FragPosition;
 out vec2 TextureCoordinates;
 out vec4 meshColour;
 out vec4 FragPosLightSpace;
 out vec3 TangentLightDir;
 out vec3 TangentViewDir;



 out mat3 TBN;



uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float time = 0;

uniform bool isScrollingTexture = false;
uniform mat4 lightSpaceMatrix;


void main()
{
   
  

    FragPosition =  vec3(model * vec4(aPos, 1.0));
		

	mat3 normalMatrix = mat3(transpose(inverse(model)));

	vec3 T = normalize(normalMatrix * aTangent);
    vec3 B = normalize(normalMatrix * aBiTangent);
    vec3 N = mat3(transpose(normalMatrix)) * aNormal;
	T = normalize(T - dot(T, N) * N);

    TBN = mat3(T, B, N);


	if(isScrollingTexture)
	{

	  TextureCoordinates = aTexCoords + vec2(0.1 * time, 0.2 * time);
	}
	else
	{
	  TextureCoordinates = aTexCoords;
	}
	 meshColour = aColor;
	 FragPosLightSpace =  lightSpaceMatrix * vec4(FragPosition, 1.0);
	 gl_Position = projection * view * vec4(FragPosition, 1.0);
}



