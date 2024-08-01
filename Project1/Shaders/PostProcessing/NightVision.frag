#version 330 core
in vec2 fragCoord;
out vec4 fragColor;

uniform sampler2D sceneTexture; 
uniform float time; 


float hash(in float n) { return fract(sin(n) * 43758.5453123); }

void main()
{
    vec2 p = fragCoord;

    vec2 u = p * 2.0 - 1.0;
    vec2 n = u * vec2(p.x / p.y, 1.0);
    vec3 c = texture(sceneTexture, p).xyz;

    // flicker, grain, vignette, fade in
    c += sin(hash(time)) * 0.01;
    c += hash((hash(n.x) + n.y) * time) * 0.5;
    c *= smoothstep(length(n * n * n * vec2(0, 0.3)), 1.0, 0.4);
    c *= smoothstep(0.001, 3.5, time) * 1.5;

    c = dot(c, vec3(0.2126, 0.7152, 0.0722)) * vec3(0.2, 1.5 - hash(time) * 0.1, 0.4);

    fragColor = vec4(c, 1.0);
}