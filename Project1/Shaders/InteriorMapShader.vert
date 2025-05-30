#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 2) in vec2 aTexCoords;
layout (location = 6) in vec2 aTangent;

out vec3 fragPos;
out vec2 vTangent;  

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

 out vec2 TextureCoordinates;

void main() 
{

    
    vec4 worldPosition = model * vec4(aPos, 1.0);
    fragPos = worldPosition.xyz;

    vTangent = aTangent;
    TextureCoordinates = aTexCoords;

    gl_Position = projection * view * worldPosition;
}