#pragma once
#include "system.h"
#include "VectorExtensions.h"
#include "components.h"
#include <SFML\System.hpp>
#include <algorithm>
#include <iostream>

class CollisionDetection :
	public System<sf::Time>
{
public:
	~CollisionDetection(void);
	CollisionDetection(Engine& engine);
	void start();
	void stop();
	void update(sf::Time timeStep);
};

