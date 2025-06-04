#pragma once
#include "../Object.h"

class EmitterProperty : public Object
{

public:
	virtual  ~EmitterProperty() = default;
	// Inherited via Object
	virtual void DrawProperties() = 0 ;
	virtual void SceneDraw() = 0;
};

