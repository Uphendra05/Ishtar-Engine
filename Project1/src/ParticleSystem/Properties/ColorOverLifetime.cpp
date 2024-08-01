#include "ColorOverLifetime.h"
#include "../../Math.h"

ColorOverLifetime::ColorOverLifetime()
{
	
}

void ColorOverLifetime::AddColorKey(ColorKey colorKey)
{
	m_ListofColorKeys.push_back(colorKey);

}

void ColorOverLifetime::AddColorKeyMap(ColorKey colorKey)
{
	m_MapofColorKeys[colorKey.keyPos] = colorKey;
}

void ColorOverLifetime::DrawProperties()
{
	float width = 150;
	DrawBoolImGui("IsEnabled", this->isEnabled);

	if (isEnabled)
	{
		for (ColorKey& color : m_ListofColorKeys)
		{
			DrawTransformVector4ImGui("Color", color.color, 1, width);

			DrawFloatImGui("Key Pos", color.keyPos);
		}
		
	}
	

}

void ColorOverLifetime::SceneDraw()
{
}

glm::vec4 ColorOverLifetime::SendColorToMat(Particle& particle)
{
	float lerpValue = MathUtils::Math::Remap(particle.currentLifetime, 0, particle.lifeTime, 1, 0);

	int colorEndIndex = 0;
	for (; colorEndIndex < m_ListofColorKeys.size(); colorEndIndex++)
	{
		if (m_ListofColorKeys[colorEndIndex].keyPos > lerpValue)
		{
			break;
		}
	}

	if (colorEndIndex >= m_ListofColorKeys.size())
	{
		return m_ListofColorKeys[colorEndIndex - 1].color;
	}

	int colorStartIndex = colorEndIndex - 1;

	ColorKey& startColor = m_ListofColorKeys[colorStartIndex];
	ColorKey& endColor = m_ListofColorKeys[colorEndIndex];

	float result = (lerpValue - startColor.keyPos) / (endColor.keyPos - startColor.keyPos);

	glm::vec4 diff = endColor.color - startColor.color;

	glm::vec4 endValue = startColor.color + diff * result;

	return endValue;

}


