#pragma once
#include "../EmitterProperty.h"
#include <vector>
#include <map>
#include "../Particle.h"
#include <iostream>

class ColorOverLifetime : public EmitterProperty
{
public:

	struct ColorKey
	{

	public:
		ColorKey(glm::vec4 color, float keyPos)
		{
			this->color = color;
			this->keyPos = keyPos;
		}
		ColorKey() {};
		glm::vec4 color = glm::vec4(1);
		float keyPos = 0;
	};

	bool isEnabled = false;
	

	ColorOverLifetime();

	void AddColorKey(ColorKey colorKey);
	void AddColorKeyMap(ColorKey colorKey);
	// Inherited via EmitterProperty
	void DrawProperties() override;
	void SceneDraw() override;

	glm::vec4 SendColorToMat(Particle& particle);


private:

	std::vector<ColorKey> m_ListofColorKeys;
	std::map <float, ColorKey > m_MapofColorKeys;

};

