#pragma once
#include <SFML\System.hpp>
#include "componentid.h"

class Position :
	public ComponentID<Position>, public sf::Vector2f
{
public:
	Position(void);
	~Position(void);
};

