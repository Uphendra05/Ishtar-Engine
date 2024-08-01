#version 330 core

out vec4 FragColor;
uniform sampler2D depthMap;
in vec2 TexCoords;

void main()
{
    float depthValue = texture(depthMap, TexCoords).r;
    FragColor = vec4(vec3(depthValue), 1.0);
};
