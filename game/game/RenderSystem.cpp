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
	// Draw stuff

	auto drawables = this->engine_.getHandles(Position::getTypeBitID() | Rectangle::getTypeBitID());
	
	sf::RenderStates rs;

	if(this->engine_.exists(Camera::getTypeBitID()))
	{
		auto camera = this->engine_.getFirstHandle(Camera::getTypeBitID() | Position::getTypeBitID());
		const Camera& cam = camera.get<Camera>();
		const Position& pos = camera.get<Position>();

		sf::Vector2f recenter((float)window.getSize().x, (float)window.getSize().y);
		recenter /= 2.0f;

		rs.transform.translate(recenter);
	
		rs.transform.rotate(cam.cameraAngle.degrees());
		rs.transform.translate(-pos);
	}

	
	const LevelData& levelData = this->engine_.getFirstHandle(LevelData::getTypeBitID()).get<LevelData>();
	sf::RectangleShape grid(sf::Vector2f(levelData.length, levelData.length));
	grid.setOutlineColor(sf::Color::Red);
	grid.setOutlineThickness(1.5f);

	for(int i = 0; i < levelData.indices->getSize(0); i++)
	{
		for(int j = 0; j < levelData.indices->getSize(1); j++)
		{
			auto tempEntity = this->engine_.getHandle(levelData.ids[levelData.indices->get(i, j)]);
			sf::Vector2f position(i * levelData.length, j * levelData.length);
			rs.transform.translate(position);
			window.draw(grid, rs);
			rs.transform.translate(-position);
		}
	}

	for(auto iter = drawables.begin(); iter != drawables.end(); iter++)
	{
		const Position& pos = iter->get<Position>();
		const Rectangle& rec = iter->get<Rectangle>();
		rs.transform.translate(pos);
		if(iter->has<Player>())
		{
			rs.transform.rotate(iter->get<Player>().rotation.degrees());
		}
		rs.transform.translate(-0.5f * rec);
		sf::RectangleShape toDraw = sf::RectangleShape(rec);
		toDraw.setFillColor(sf::Color::Black);
		window.draw(toDraw, rs);
		rs.transform.translate(0.5f * rec);
		if(iter->has<Player>())
		{
			rs.transform.rotate(-iter->get<Player>().rotation.degrees());
		}
		rs.transform.translate(-pos);
	}


    // Update the window
    window.display();
}