#version 330 core
out vec4 FragColor;

in vec3 fragPos;

uniform vec3 cameraPos;
uniform samplerCube interiorCubemap;

const float NUM_ROOMS_X = 1.0;
const float NUM_ROOMS_Y = 1.0;

void main() 
{  
  vec3 viewDir = normalize(fragPos - cameraPos);  // Camera Forward

  vec3 scaledPos = fragPos;
  scaledPos.x *= NUM_ROOMS_X;
  scaledPos.y *= NUM_ROOMS_Y;

  vec3 localPos = fract(scaledPos);  //Isolating the local positions within the cube


  vec3 boxMin = (vec3(0.0)-localPos)/viewDir;
  vec3 boxMax = (vec3(1.0)-localPos)/viewDir;

  vec3 t1 = min(boxMin, boxMax);
  vec3 t2 = max(boxMin, boxMax);

  float tNear = max(max(t1.x, t1.y), t1.z);
  float tFar  = min(min(t2.x, t2.y), t2.z);


  vec3 hitPos = localPos + viewDir * tFar; // Finding the hit position within the each cube section


  vec3 cubeDir = normalize(hitPos - vec3(0.5)); //normalizing the segments direction

  vec3 result = texture(interiorCubemap, cubeDir).rgb;

  FragColor = vec4(result,1);


}