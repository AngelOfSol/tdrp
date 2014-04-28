#pragma once
#include <SFML\System.hpp>
#include "system.h"
#include "ComponentList.h"
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
class RenderSystem :
	public System<sf::Time>
{
public:
	~RenderSystem(void);
	
	RenderSystem(EntityEngine& engine, ComponentEngine& componentEngine, sf::RenderWindow& renderWindow);
	void start();
	void stop();
	void update(sf::Time timeStep);
private:
	sf::RenderWindow& window;
};

