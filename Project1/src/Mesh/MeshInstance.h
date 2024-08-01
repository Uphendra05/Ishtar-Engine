#pragma once
#include  "../model.h"


struct TransformData
{
	TransformData() = default;

	TransformData(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
		: position(position), rotation(rotation), scale(scale)
	{

	}
	glm::vec3 position{ 0 };
	glm::vec3 rotation{ 0 };
	glm::vec3 scale{ 1 };
};

class MeshInstance : public Model
{
public:
	virtual void Draw(Shader* shader) override;
	void AddTransformData(const TransformData& transformData = TransformData(glm::vec3(0), glm::vec3(0), glm::vec3(1)));
	void AddTransformData(const glm::vec3& position =  glm::vec3(0), const glm::vec3& rotation = glm::vec3(0), const glm::vec3 scale = glm::vec3(1));

	virtual void DrawProperties() override;
	virtual void SceneDraw() override;

	virtual void Start() override {};
	virtual void Update(float deltaTime) override {};
	virtual void Render()  override {};
	virtual void OnDestroy()  override {};
private:

	std::vector<glm::mat4> listOfMatices;
	std::vector<TransformData> meshTransformDataList;

};

