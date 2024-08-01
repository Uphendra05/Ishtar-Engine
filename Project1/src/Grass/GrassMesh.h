#pragma once
#include "../Mesh/MeshInstance.h"
class GrassMesh : public MeshInstance
{
public:
	GrassMesh();


	 void Draw(Shader* shader) override;
	

	 void DrawProperties() override;
	 void SceneDraw() override;

	 void Start() override {};
	 void Update(float deltaTime) override;
	 void Render()  override {};
	 void OnDestroy() override {};

private:
	  std::string diffuseTexurePath = "Models/Grass/GrassThree.png";
	  std::string alphaTexurePath = "Models/Grass/alpha3.png";
	  Shader* grassShader = nullptr;
	  float time = 10;
	  float windStrength = 40.0f;
	  float windDensity = 0.60f;
	  float grassHeight = 0.35f;

	  glm::vec2 windDirection = glm::vec2(0.40f, 0);

};


