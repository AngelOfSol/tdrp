#pragma once
#include "componentid.h"

/*
	Flags an enitity as containing input data.
*/


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

