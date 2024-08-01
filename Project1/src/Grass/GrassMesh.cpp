#include "GrassMesh.h"
#include "../GraphicsRender.h"
#include "../Time.h"
#include "../Math.h"
GrassMesh::GrassMesh()
{
	grassShader = GraphicsRender::GetInstance().grassInstanceShader;

	LoadModel("Models/Grass/Grass.fbx");

  Texture* diffuseTexture = new Texture(diffuseTexurePath);
  Texture* alphaTexture = new Texture(alphaTexurePath);
  for (std::shared_ptr<Mesh> mesh :  meshes)
  {
	  mesh->meshMaterial->material()->diffuseTexture = diffuseTexture;
	  mesh->meshMaterial->material()->specularTexture = diffuseTexture;
	  
	  mesh->meshMaterial->material()->alphaTexture = alphaTexture;
	  mesh->meshMaterial->material()->useMaskTexture = true;
  }
}

void GrassMesh::Draw(Shader* shader)
{
	time += Time::GetInstance().deltaTime;
	if (time> 200)
	{
		// clamping time
		time = 20;
	}
	//time += (float)glfwGetTime();
	shader->Bind();
	shader->setFloat("time", time);
	shader->setVec2("windDirection", windDirection);
	shader->setFloat("windStrength", windStrength);
	shader->setFloat("windDensity", windDensity);
	shader->setFloat("grassHeight", grassHeight);
	MeshInstance::Draw(shader);
}

void GrassMesh::DrawProperties()
{
	MeshInstance::DrawProperties();

	if (!ImGui::TreeNodeEx("Grass Properties", ImGuiTreeNodeFlags_DefaultOpen))
	{
		return;
	}
	float column = 150;
	DrawDragFloatImGui("Time", time);
	DrawTransformVector2ImGui("windDirection", windDirection, 0, column);
	DrawDragFloatImGui("windStrength", windStrength);
	DrawDragFloatImGui("windDensity", windDensity);
	DrawDragFloatImGui("grassHeight", grassHeight,0.01f,0.0f,1.0f);

	ImGui::TreePop();
}

void GrassMesh::SceneDraw()
{
	MeshInstance::SceneDraw();
}

void GrassMesh::Update(float deltaTime)
{
}
