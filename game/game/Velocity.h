#pragma once
#include "componentid.h"
#include <SFML\System.hpp>

/*
	Flags and gives an entity a velocity.
*/

class Velocity :
	public ComponentID<Velocity>, public sf::Vector2f
{
public:
	Velocity(void);
	~Velocity(void);
};

