#include "ParticleEmission.h"


ParticleEmission::ParticleEmission()
{
	m_ParticleModel = new ParticleModel();
}



void ParticleEmission::AddBurst(Burst burstInfo)
{
	m_ListOfBursts.push_back(burstInfo);
}

void ParticleEmission::RemoveBurst(int index)
{
	std::vector<Burst>::iterator it = m_ListOfBursts.begin() + index;

	m_ListOfBursts.erase(it);

}

void ParticleEmission::BurstProperties(Burst& infor, int index)
{

	if (!ImGui::TreeNodeEx(("Burst " + std::to_string(index)).c_str()))
	{
		return;
	}
	DrawFloatImGui("Time", infor.time);
	DrawIntImGui("Count", infor.count);
	DrawIntImGui("Cycles", infor.cycles);
	DrawFloatImGui("Interval", infor.interval);
	DrawFloatImGui("Probability", infor.probability);

	ImGui::TreePop();
}

void ParticleEmission::DrawProperties()
{
	DrawFloatImGui("Rate Over Time", rateOverTime);

	DrawFloatImGui("Max Particle Size", m_ParticleModel->maxParticleSize);
	DrawFloatImGui("Min Particle Size", m_ParticleModel->minParticleSize);

	for (int i = 0; i < m_ListOfBursts.size(); i++)
	{
		BurstProperties(m_ListOfBursts[i], i);
	}
}

void ParticleEmission::SceneDraw()
{
}
