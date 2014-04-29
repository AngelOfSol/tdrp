#include "RenderSystem.h"


RenderSystem::RenderSystem(EntityEngine& engine, ComponentEngine& componentEngine, sf::RenderWindow& renderWindow):System(engine, componentEngine), window(renderWindow)
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

	std::vector<entity_id> drawables = this->entitiesList_.getEntitys(PositionComponent::getTypeBitID() | RectangleComponent::getTypeBitID());
	
	sf::RenderStates rs;

	entity_id camera = this->entitiesList_.getFirstEntity(CameraComponent::getTypeBitID());

	const CameraComponent& cam = this->componentsList_.getComponent<CameraComponent>(this->entitiesList_.getComponent<CameraComponent>(camera));


	sf::Vector2f recenter((float)window.getSize().x, (float)window.getSize().y);
	recenter /= 2.0f;

	rs.transform.translate(recenter);
	
	rs.transform.rotate(cam.cameraAngle.degrees());
	rs.transform.translate(-cam);

	for(auto iter = drawables.begin(); iter != drawables.end(); iter++)
	{
		const PositionComponent& pos = this->componentsList_.getComponent<PositionComponent>(this->entitiesList_.getComponent<PositionComponent>(*iter));
		const RectangleComponent& rec = this->componentsList_.getComponent<RectangleComponent>(this->entitiesList_.getComponent<RectangleComponent>(*iter));
		rs.transform.translate(pos);
		sf::RectangleShape toDraw = sf::RectangleShape(rec);
		toDraw.setFillColor(sf::Color::Black);
		window.draw(toDraw, rs);
		rs.transform.translate(-pos);
	}

    // Update the window
    window.display();
}