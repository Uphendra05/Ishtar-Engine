#pragma once
#include "../model.h"
#include "../ApplicationRenderer.h"

class InteriorMapping : public Model
{
public :

	InteriorMapping();
	InteriorMapping(ApplicationRenderer* applicaiton);
	~InteriorMapping();

	
	void Init();
	void Draw(Shader* shader) override;
	void DrawProperties() override;
	void SceneDraw() override;

	void Start() override {};
	void Update(float deltaTime) override;
	void Render()  override {};
	void OnDestroy() override {};
	
private:
	ApplicationRenderer* application = nullptr;
	bool useDefaultShader = true;
	float noOfRoomsX = 1.0f;
	float noOfRoomY =  1.0f;
	Texture* buildingTexture = nullptr;
	Texture* alphaTextrue = nullptr;

		
};

