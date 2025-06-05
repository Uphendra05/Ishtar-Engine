#version 330 core
layout (location = 0) out vec4 FragColor;



uniform vec3 objectColor;

void main()
{
    FragColor = vec4(1.0*objectColor,1.0); 
}