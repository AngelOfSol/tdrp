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

	std::vector<entity_id> drawables = this->engine_.getEntitys(Position::getTypeBitID() | Rectangle::getTypeBitID());
	
	sf::RenderStates rs;

	if(this->engine_.exists(Camera::getTypeBitID()))
	{
		entity_id camera = this->engine_.getFirstEntity(Camera::getTypeBitID());
		const Camera& cam = this->engine_.getComponentOf<Camera>(camera);


		sf::Vector2f recenter((float)window.getSize().x, (float)window.getSize().y);
		recenter /= 2.0f;

		rs.transform.translate(recenter);
	
		rs.transform.rotate(cam.cameraAngle.degrees());
		rs.transform.translate(-cam);
	}
	for(auto iter = drawables.begin(); iter != drawables.end(); iter++)
	{
		const Position& pos = this->engine_.getComponentOf<Position>(*iter);
		const Rectangle& rec = this->engine_.getComponentOf<Rectangle>(*iter);
		rs.transform.translate(pos);
		if(this->engine_.hasComponent<Player>(*iter))
		{
			rs.transform.rotate(this->engine_.getComponentOf<Player>(*iter).rotation.degrees());
		}
		rs.transform.translate(-0.5f * rec);
		sf::RectangleShape toDraw = sf::RectangleShape(rec);
		toDraw.setFillColor(sf::Color::Black);
		window.draw(toDraw, rs);
		rs.transform.translate(0.5f * rec);
		if(this->engine_.hasComponent<Player>(*iter))
		{
			rs.transform.rotate(-this->engine_.getComponentOf<Player>(*iter).rotation.degrees());
		}
		rs.transform.translate(-pos);
	}

    // Update the window
    window.display();
}