#include <iostream>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>

int main()
{
	
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(640, 480), "Test", sf::Style::Default, settings);

	sf::Clock timer;

	sf::Time minimiumFrameTime = sf::seconds(1.0f / 60.0f);
	sf::Event event;
	int elapsedTotal = 0;
		sf::RenderStates rs;
	while(window.isOpen())
	{
		 while (window.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                window.close();
			
        }
		
        // Clear screen
        window.clear(sf::Color(255, 255, 255, 255));
		// Draw stuff
        // Update the window
        window.display();
	}
	return 0;
}