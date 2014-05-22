#pragma once
#include <SFML\System.hpp>
#include "componentid.h"

/*
	Flags and gives an entity a position.
*/

class Position :
	public ComponentID<Position>, public sf::Vector2f
{
public:
	Position(void);
	~Position(void);
};

