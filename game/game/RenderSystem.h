#pragma once
#include <SFML\System.hpp>
#include "system.h"
#include "components.h"
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <iostream>
class RenderSystem :
	public System<sf::Time>
{
public:
	~RenderSystem(void);
	
	RenderSystem(Engine& engine, sf::RenderWindow& renderWindow);
	void start();
	void stop();
	void update(sf::Time timeStep);
private:
	sf::RenderWindow& window;
};

