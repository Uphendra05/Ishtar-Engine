#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 s_TexCoords;
out vec4 fragPos;

uniform mat4 projection;
uniform mat4 view;

void main()
{
    s_TexCoords = aPos;
    fragPos = projection * view * vec4(aPos, 1.0);
    gl_Position = fragPos.xyww;
}  