#pragma once
#include "componentid.h"
class InputData :
	public ComponentID<InputData>
{
public:
	InputData(void);
	~InputData(void);
	bool leftKey;
	bool rightKey;
	bool upKey;
	bool downKey;
};

