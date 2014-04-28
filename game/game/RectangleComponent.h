#pragma once
#include <SFML\System.hpp>
#include "componentid.h"
class RectangleComponent :
	public ComponentID<RectangleComponent>, public sf::Vector2f
{
public:
	RectangleComponent(void);
	~RectangleComponent(void);
};

