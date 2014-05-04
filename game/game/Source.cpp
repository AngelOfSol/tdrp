#include <iostream>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include "RenderSystem.h"
#include "Input.h"
#include "Physics.h"
#include "ComponentEngine.h"
#include "EntityEngine.h"
#include "ComponentList.h"
#include "Engine.h"
int main()
{
	
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(640, 480), "Test", sf::Style::Default, settings);
	
	Engine engine;
	
	entity_id inputID = engine.getNewEntity();

	engine.addComponentTo<InputData>(inputID);

	InputData& input = engine.getComponentOf<InputData>(inputID);

	entity_id player = engine.getNewEntity();
	
	engine.addComponentTo<Position>(player);
	
	engine.getComponentOf<Position>(player).x = 0;
	engine.getComponentOf<Position>(player).y = 0;

	engine.addComponentTo<Rectangle>(player);
	
	engine.getComponentOf<Rectangle>(player).x = 20;
	engine.getComponentOf<Rectangle>(player).y = 20;

	engine.addComponentTo<Acceleration>(player);
	engine.addComponentTo<Velocity>(player);
	engine.addComponentTo<Player>(player);

	entity_id camera = engine.getNewEntity();

	engine.addComponentTo<Camera>(camera);

	Camera& cam = engine.getComponentOf<Camera>(camera);

	cam.x = 0;
	cam.y = 0;

	cam.cameraAngle = Angle<float>(DEGREE, 0);
	
	std::vector<System<sf::Time>*> systems;

	
	systems.push_back(new Input(engine));
	systems.push_back(new Physics(engine));
	systems.push_back(new RenderSystem(engine, window));
	
	sf::Clock timer;

	sf::Time minimiumFrameTime = sf::seconds(1.0f / 60.0f);
	sf::Event event;
	sf::Time elapsedTotal;


	while(window.isOpen())
	{
		sf::Time elapsed = timer.restart();
		while (window.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				switch(event.key.code)
				{
				case sf::Keyboard::Up:
					input.upKey = true;
					break;
				case sf::Keyboard::Down:
					input.downKey = true;
					break;
				case sf::Keyboard::Left:
					input.leftKey = true;
					break;
				case sf::Keyboard::Right:
					input.rightKey = true;
					break;
				}
			} else if (event.type == sf::Event::KeyReleased)
			{
				switch(event.key.code)
				{
				case sf::Keyboard::Up:
					input.upKey = false;
					break;
				case sf::Keyboard::Down:
					input.downKey = false;
					break;
				case sf::Keyboard::Left:
					input.leftKey = false;
					break;
				case sf::Keyboard::Right:
					input.rightKey = false;
					break;
				}
			}
        }
		
		for(auto iter = systems.begin(); iter != systems.end(); iter++)
		{
			(*iter)->update(elapsed);
		}
		


	}
	return 0;
}