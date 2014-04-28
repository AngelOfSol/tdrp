#pragma once
#include <SFML\System.hpp>
#include "componentid.h"

class PositionComponent :
	public ComponentID<PositionComponent>, public sf::Vector2f
{
public:
	PositionComponent(void);
	~PositionComponent(void);
};

