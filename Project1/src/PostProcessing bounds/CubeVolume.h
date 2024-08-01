#pragma once
#include "BaseVolume.h"
class CubeVolume : public BaseVolume
{
public:
	CubeVolume();

	void SetExtends(const glm::vec3& extends);
	void DrawVolume() override;
	virtual void Start()  override {};
	virtual void Update(float deltaTime) override {};
	virtual void OnDestroy() override {};
	virtual void OnTriggerEnter(PhysXObject* otherObject) override;
	virtual void OnTriggerExit(PhysXObject* otherObject)  override;
private:
	glm::vec3 extends;
};

