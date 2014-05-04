#pragma once
#include "componentid.h"
#include <SFML\System.hpp>
class Velocity :
	public ComponentID<Velocity>, public sf::Vector2f
{
public:
	Velocity(void);
	~Velocity(void);
};

