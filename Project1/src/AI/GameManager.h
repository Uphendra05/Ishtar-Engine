#pragma once
#include "../EntityManager/EntityManager.h"
#include "../Player/PlayerController.h"
#include "Enemy.h"
class GameManager : public Entity
{
public:
	GameManager();

	void Start() override;
	void Update(float deltaTime) override;
	void OnDestroy() override;
	void Render() override;
	void DrawProperties() override;
	void SceneDraw() override;

	void AddEnemies(Enemy* enemy);

	PlayerController* player = nullptr;

private:

	std::vector<Enemy*> listOfEnimies;

};

