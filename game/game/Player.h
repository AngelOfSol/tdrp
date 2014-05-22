#pragma once
#include "componentid.h"
#include "Angle.h"

/*
	Flags an entity as a player and gives them a rotation.
*/

class Player :
	public ComponentID<Player>
{
public:
	Player(void);
	~Player(void);

	float accel;
	float friction;
	float brakes;
	Angle<float> turnAngle;
	float turnMultiplier;
	float maxSpeed;
};

