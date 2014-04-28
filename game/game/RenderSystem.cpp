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

	std::vector<Entity*> drawables = this->entitiesList_.getEntitys(PositionComponent::getTypeID() | RectangleComponent::getTypeID());
	
	sf::RenderStates rs;

	Entity* camera = this->entitiesList_.getFirstEntity(CameraComponent::getTypeID());

	const CameraComponent& cam = *this->componentsList_.getComponentOf<CameraComponent>(*camera);


	sf::Vector2f recenter(window.getSize().x, window.getSize().y);
	recenter /= 2.0f;

	rs.transform.translate(recenter);
	
	rs.transform.rotate(cam.cameraAngle.degrees());
	rs.transform.translate(-cam);

	for(auto iter = drawables.begin(); iter != drawables.end(); iter++)
	{
		Entity& ent = **iter;
		const PositionComponent& pos = *this->componentsList_.getComponentOf<PositionComponent>(ent);
		const RectangleComponent& rec = *this->componentsList_.getComponentOf<RectangleComponent>(ent);
		rs.transform.translate(pos);
		sf::RectangleShape toDraw = sf::RectangleShape(rec);
		toDraw.setFillColor(sf::Color::Black);
		window.draw(toDraw, rs);
		rs.transform.translate(-pos);
	}

    // Update the window
    window.display();
}