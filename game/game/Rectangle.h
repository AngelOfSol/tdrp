#pragma once
#include <SFML\System.hpp>
#include "componentid.h"

/*
	Flags and gives an entity a bounding box.

	The rectangle referenced is centered (i.e. it goes from -x/2 to +x/2).
*/

class Rectangle :
	public ComponentID<Rectangle>, public sf::Vector2f
{
public:
	Rectangle(void);
	~Rectangle(void);
};

