#version 330 core
out vec4 FragColor;

in vec3 fragPos;
in vec2 vTangent;
in vec2 TextureCoordinates;


uniform samplerCube interiorCubemap;
uniform sampler2D diffuse_Texture;
uniform sampler2D specular_Texture;  
uniform sampler2D opacity_Texture;
uniform vec3 cameraPos;
uniform float NUM_ROOMS_X;
uniform float NUM_ROOMS_Y;

void main() 
{  

 
 
  vec3 viewDir = normalize(fragPos - cameraPos);  // Ray Simulation

  vec3 scaledPos = fragPos; // Tiling the Interior Mapping
  scaledPos.x *= NUM_ROOMS_X;
  scaledPos.y *= NUM_ROOMS_Y;

  vec3 localPos = fract(scaledPos);  //Isolating the local positions within the cube



  // Basic Ray AABB Collision
  vec3 boxMin = (vec3(0.0)-localPos)/viewDir;
  vec3 boxMax = (vec3(1.0)-localPos)/viewDir;

  vec3 t1 = min(boxMin, boxMax);
  vec3 t2 = max(boxMin, boxMax);

  float tNear = max(max(t1.x, t1.y), t1.z);
  float tFar  = min(min(t2.x, t2.y), t2.z);


  vec3 hitPos = localPos + viewDir * tFar  ; // Finding the hit position within the each cube section


  vec3 cubeDir = normalize(hitPos  - vec3(0.5)); //normalizing the segments direction

  vec3 result = texture(interiorCubemap, cubeDir).rgb;

  // Sample wall texture (with alpha for windows)
    vec4 wall = texture(diffuse_Texture, TextureCoordinates);

    vec3 finalColor = mix(result, wall.rgb, wall.a);

  FragColor = vec4(result,1);


}