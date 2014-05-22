#pragma once
#include "componentid.h"
#include "Angle.h"
class Rotation :
	public ComponentID<Rotation>
{
public:
	Rotation(void);
	~Rotation(void);

	Angle<float> value;
};

