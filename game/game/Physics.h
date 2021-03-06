#pragma once
#include "system.h"
#include "components.h"
#include "VectorExtensions.h"
#include <iostream>
#include <SFML\System.hpp>
/*
	A system to handle physics.
*/

class Physics :
	public System<sf::Time>
{
public:
	~Physics(void);
	Physics(Engine& engine);
	void start();
	void stop();
	void update(sf::Time timeStep);
};

