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
#include "CollisionDetection.h"
#include "mdarray.h"
int main()
{

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(640, 480), "Test", sf::Style::Default, settings);
	
	Engine engine;
	
	auto inputEntity = engine.getNewHandle();
	

	inputEntity.add<InputData>();

	InputData& input = inputEntity.get<InputData>();

	auto player = engine.getNewHandle();
	
	player.add<Position>();
	
	player.get<Position>().x = 0;
	player.get<Position>().y = 0;

	player.add<Rectangle>();
	
	player.get<Rectangle>().x = 20;
	player.get<Rectangle>().y = 20;

	player.add<Player>();

	Player& playerData = player.get<Player>();

	playerData.accel = 120.0f;
	playerData.brakes = -0.99f;
	playerData.turnAngle = Angle<float>(DEGREE, 100.0f);
	playerData.turnMultiplier = 2.0f;
	playerData.friction = 0.3f;
	playerData.maxSpeed = 600.0f;

	player.add<Acceleration>();
	player.add<Velocity>();
	player.add<Camera>();
	player.add<Rotation>();

	std::vector<System<sf::Time>*> systems;

	auto levelData = engine.getNewHandle();

	levelData.add<LevelData>();

	LevelData& data = levelData.get<LevelData>();

	data.indices = new md_array<int, 2>(400, 400);
	
	auto tileEntity = engine.getNewEntity();
	auto collidedTileEntity = engine.getNewEntity();
	
	data.ids.push_back(tileEntity);
	data.ids.push_back(collidedTileEntity);

	for(int i = 0; i < data.indices->getSize(0); i++)
	{
		for(int j = 0; j < data.indices->getSize(0); j++)
		{
			data.indices->get(i, j) = 0;
		}
	}

	data.length = 32;



	
	systems.push_back(new Input(engine));
	systems.push_back(new Physics(engine));
	systems.push_back(new RenderSystem(engine, window));
	systems.push_back(new CollisionDetection(engine));
	


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