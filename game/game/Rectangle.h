#pragma once
#include <SFML\System.hpp>
#include "componentid.h"
class Rectangle :
	public ComponentID<Rectangle>, public sf::Vector2f
{
public:
	Rectangle(void);
	~Rectangle(void);
};

