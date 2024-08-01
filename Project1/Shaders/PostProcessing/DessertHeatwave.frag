#version 330 core
in vec2 uv;
out vec4 FragColor;

uniform sampler2D sceneTexture;
uniform sampler2D noiseTexture;
uniform sampler2D sandTexture;

uniform float time;


uniform float distortAmount = 0.0015;
uniform float distortZoom = 1.2;
uniform float distortSpeed = 0.1;
uniform float lerpIntensity = 0.6;

vec3 mainColor = vec3(0.5, 0.45, 0.4) * 0.8;

void main()
{
    vec2 uv1 = uv;

	  float distortNoise = texture(sceneTexture, vec2(fract(uv1.x * distortZoom - time * distortSpeed), uv1.y * distortZoom)).r;
    
    distortNoise = smoothstep(0.11, 0.45, distortNoise);

    vec2 distortUV = (vec2(distortNoise * 1., distortNoise * 1.) * distortAmount);

	 vec4 color = texture(sceneTexture, uv1 + distortUV);

	 float sandNoise = texture(sandTexture, vec2(fract(uv1.x - time * 0.8), fract(uv1.y + time * 0.055)) + distortUV).r;
     float sandNoise2 = texture(sandTexture, vec2(fract(uv1.x * 1.2 - time * 0.4), fract(uv1.y * 1.2 + time * 0.06)) + distortUV).r;
     float sandNoise3 = texture(sandTexture, vec2(fract(uv1.x * 0.8 - time * 0.6), fract(uv1.y * 0.8 + time * 0.035)) + distortUV).r;

	float finalSandNoise = sandNoise * 0.233 + sandNoise2 * 0.433 + sandNoise3 * 0.333;

	 float sineLerpModifier = (1. + sin(3.1415 * time * 0.4)) * 0.5;

    color = mix(color, vec4(mainColor, 1.), lerpIntensity * sineLerpModifier);  

    color += vec4(mainColor, 1.) * mix(0.2, 1.0, finalSandNoise * mix(0.5, 0.9, sineLerpModifier));
 
	
    FragColor = color;

}