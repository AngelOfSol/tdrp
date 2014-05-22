#pragma once
#include <SFML\System.hpp>
#include "componentid.h"

/*
	Flags and gives an entity an Acceleration.
*/

class Acceleration :
	public ComponentID<Acceleration>, public sf::Vector2f
{
public:
	Acceleration(void);
	~Acceleration(void);

};

