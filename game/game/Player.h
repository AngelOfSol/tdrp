#pragma once
#include "componentid.h"
#include "Angle.h"
class Player :
	public ComponentID<Player>
{
public:
	Player(void);
	~Player(void);
	Angle<float> rotation;
};

