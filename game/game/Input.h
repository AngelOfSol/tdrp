#pragma once
#include "system.h"
#include "VectorExtensions.h"
#include <algorithm>
#include "components.h"
#include <iostream>
#include <SFML\Window.hpp>
/*
	A system to handle input.
*/
class Input :
	public System<sf::Time>
{
public:
	Input(Engine&);
	~Input(void);
	void start();
	void stop();
	void update(sf::Time timeStep);
};
