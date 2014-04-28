#include <iostream>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include "RenderSystem.h"
#include "ComponentEngine.h"
#include "EntityEngine.h"
#include "ComponentList.h"
int main()
{
	
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(640, 480), "Test", sf::Style::Default, settings);

	ComponentEngine comp;
	EntityEngine ent;

	
	Entity* block = ent.getNewEntityPointer();
	
	comp.giveNewComponent<PositionComponent>(*block);
	comp.giveNewComponent<RectangleComponent>(*block);
	
	PositionComponent& pos = *comp.getComponentOf<PositionComponent>(*block);
	RectangleComponent& rec = *comp.getComponentOf<RectangleComponent>(*block);

	pos.x = 0;
	pos.y = 0;

	rec.x = 20;
	rec.y = 20;

	Entity* block2 = ent.getNewEntityPointer();
	
	comp.giveNewComponent<PositionComponent>(*block2);
	comp.giveNewComponent<RectangleComponent>(*block2);
	
	PositionComponent& pos2 = *comp.getComponentOf<PositionComponent>(*block2);
	RectangleComponent& rec2 = *comp.getComponentOf<RectangleComponent>(*block2);

	pos2.x = 100;
	pos2.y = 100;

	rec2.x = 30;
	rec2.y = 30;


	Entity* camera = ent.getNewEntityPointer();

	comp.giveNewComponent<CameraComponent>(*camera);

	CameraComponent& cam = *comp.getComponentOf<CameraComponent>(*camera);

	cam.x = 0;
	cam.y = 0;

	cam.cameraAngle = Angle<float>(DEGREE, 0);

	RenderSystem rend(ent, comp, window);

	sf::Clock timer;

	sf::Time minimiumFrameTime = sf::seconds(1.0f / 60.0f);
	sf::Event event;
	int elapsedTotal = 0;


	while(window.isOpen())
	{
		while (window.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                window.close();
			
        }
		sf::Time elapsed = timer.restart();
		elapsedTotal += (int)elapsed.asMicroseconds();
		while (elapsedTotal >= minimiumFrameTime.asMicroseconds())
		{
			elapsedTotal %= minimiumFrameTime.asMicroseconds();
			cam.cameraAngle += Angle<float>(DEGREE, 1);
			cam.x += 0.3f;
			cam.y += 0.3f;
		}


		rend.update(sf::seconds(1));
	}
	return 0;
}