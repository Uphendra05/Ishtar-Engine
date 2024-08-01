#include "GameManager.h"

GameManager::GameManager()
{

	name = "Game Manager";
	InitializeEntity(this);
}

void GameManager::Start()
{
}

void GameManager::Update(float deltaTime)
{
}

void GameManager::OnDestroy()
{
}

void GameManager::Render()
{
}

void GameManager::DrawProperties()
{
	Entity::DrawProperties();



	ImGui::NewLine();
	if (!ImGui::TreeNodeEx("Game manager", ImGuiTreeNodeFlags_DefaultOpen))
	{
		return;
	}


	if (listOfEnimies.size() > 0)
	{
		for (int i = 0; i < listOfEnimies.size(); i++)
		{
			std::string name = listOfEnimies[i]->name + " ShowDebug";
			DrawBoolImGui(name, listOfEnimies[i]->showDebug, 250);

			DrawDragFloatImGui("EnemyWalkSpeed", listOfEnimies[i]->enemyMoveSpeed, 0.01f, 0.25f,10, 250);
			DrawDragFloatImGui("RangeSpeed", listOfEnimies[i]->enemyRangeSpeed, 0.01f, 0.25f, 20, 250);
			DrawDragFloatImGui("InnerRadius", listOfEnimies[i]->InnerRadius, 0.01f, 0.25f, 100,250);
			DrawDragFloatImGui("OuterRadius", listOfEnimies[i]->OuterRadius, 0.01f, 0.25f, 100, 250);
		}
	}
	

	DrawBoolImGui("Player debug", player->showDebug, 250);
	DrawDragFloatImGui("Player Speed", player->playerMoveSpeed, 0.01f, 2.5f,25.0f,250.0f);


	ImGui::TreePop();
	

}

void GameManager::SceneDraw()
{
	Entity::SceneDraw();
}

void GameManager::AddEnemies(Enemy* enemy)
{
	listOfEnimies.push_back(enemy);
}
