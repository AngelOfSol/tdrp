#include "RenderSystem.h"


RenderSystem::RenderSystem(Engine& engine, sf::RenderWindow& renderWindow):System(engine), window(renderWindow)
{
}


RenderSystem::~RenderSystem(void)
{
}
void RenderSystem::start()
{
}
void RenderSystem::stop()
{
}
void RenderSystem::update(sf::Time timeStep)
{
    // Clear screen
    window.clear(sf::Color(255, 255, 255, 255));

	// Draw stuff if we have a camera

	if(this->engine_.exists(Camera::getTypeBitID() | Position::getTypeBitID() | Rotation::getTypeBitID()))
	{
		// get a list of stuff to draw

		auto drawables = this->engine_.getHandles(Position::getTypeBitID() | Rectangle::getTypeBitID());
	
		sf::RenderStates rs;

		// grab the camera

		auto camera = this->engine_.getFirstHandle(Camera::getTypeBitID() | Position::getTypeBitID() | Rotation::getTypeBitID());
		const Position& cameraPos = camera.get<Position>();
		const Rotation& cameraAngle = camera.get<Rotation>() ;

		// center the window, making the center of the window (0,0)

		sf::Vector2f recenter((float)window.getSize().x, (float)window.getSize().y);
		recenter /= 2.0f;

		rs.transform.translate(recenter);
	
		// rotate the window to match the camera, and then move the window to match the camera

		rs.transform.rotate(-cameraAngle.value.degrees() - 90);
		rs.transform.translate(-cameraPos);
	
		// grab the level data
	
		const LevelData& levelData = this->engine_.getFirstHandle(LevelData::getTypeBitID()).get<LevelData>();

		// create a default grid shape

		sf::RectangleShape grid(sf::Vector2f(levelData.length, levelData.length));
		grid.setOutlineColor(sf::Color::Black);
		grid.setOutlineThickness(1.5f);

		// cull out grid squares there aren't in the window

		sf::Vector2f lowerBound;
		sf::Vector2f upperBound;
		
		sf::Vector2f windowSize;
		
		windowSize.x = window.getSize().x;
		windowSize.y = window.getSize().y;

		jck::vector::createBounds(cameraPos / (float) levelData.length, windowSize / (1.0f * levelData.length), &lowerBound, &upperBound);
		
		lowerBound = jck::vector::max(lowerBound, sf::Vector2f(0.0f, 0.0f));
		upperBound = jck::vector::min(upperBound, sf::Vector2f(levelData.indices->getSize(0), levelData.indices->getSize(1)));


		for(int i = lowerBound.x; i < upperBound.x; i++)
		{
			for(int j = lowerBound.y; j < upperBound.y; j++)
			{

				// draw the entity to the window

				auto tempEntity = this->engine_.getHandle(levelData.ids[levelData.indices->get(i, j)]);
				sf::Vector2f cameraPosition(i * levelData.length, j * levelData.length);
				
				if(levelData.indices->get(i, j) == 0)
					grid.setFillColor(sf::Color::Red);
				else if(levelData.indices->get(i, j) == 1)
					grid.setFillColor(sf::Color::Blue);

				rs.transform.translate(cameraPosition);
				window.draw(grid, rs);
				rs.transform.translate(-cameraPosition);
				
			}
		}

		for(auto iter = drawables.begin(); iter != drawables.end(); iter++)
		{

			//
			const Position& pos = iter->get<Position>();
			const Rectangle& rec = iter->get<Rectangle>();
			rs.transform.translate(pos);
			if(iter->has<Rotation>())
			{
				rs.transform.rotate(iter->get<Rotation>().value.degrees());
			}
			rs.transform.translate(-0.5f * rec);
			sf::RectangleShape toDraw = sf::RectangleShape(rec);
			toDraw.setFillColor(sf::Color::Black);
			window.draw(toDraw, rs);
			rs.transform.translate(0.5f * rec);
			if(iter->has<Rotation>())
			{
				rs.transform.rotate(-iter->get<Rotation>().value.degrees());
			}
			rs.transform.translate(-pos);
		}
	}

    // Update the window
    window.display();
}