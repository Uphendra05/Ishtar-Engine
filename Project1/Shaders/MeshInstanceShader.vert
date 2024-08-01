#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec4 aColor;


 out vec3 FragPosition;
 out vec3 Normal;
 out vec2 TextureCoordinates;
 out vec4 meshColour;

uniform mat4 view;
uniform mat4 projection;
uniform float time = 0;
uniform mat4 instanceModel[100];

uniform bool isScrollingTexture;

// function prototypes

void main()
{

     mat4 instanceModelID = instanceModel[gl_InstanceID]; 

     vec3 instancedPos = vec3(instanceModelID * vec4(aPos, 1.0));
   
    FragPosition = instancedPos;
    Normal =  mat3(transpose(inverse(instanceModelID))) * aNormal;
	if(isScrollingTexture)
	{

	  TextureCoordinates = aTexCoords + vec2(0.1 * time, 0.2 * time);
	}
	else
	{
	  TextureCoordinates = aTexCoords;
	}
	 meshColour = aColor;
	//gl_Position = projection * view * model;
	  gl_Position = projection * view * vec4(instancedPos, 1.0);
}



