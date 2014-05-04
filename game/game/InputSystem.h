#pragma once
#include "system.h"
#include <SFML\System.hpp>

class InputSystem :
	public System<sf::Time>
{
public:
	~InputSystem(void);
	
	InputSystem(Engine& engine);
	void start();
	void stop();
	void update(sf::Time timeStep);

private:


};

