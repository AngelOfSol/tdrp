#include "Physics.h"


Physics::Physics(Engine& engine):System(engine)
{
}


Physics::~Physics(void)
{
}


void Physics::start()
{
}

void Physics::stop()
{
}

void Physics::update(sf::Time elapsed)
{
	
	std::vector<entity_id> accelerators = this->engine_.getEntitys(Acceleration::getTypeBitID() | Velocity::getTypeBitID());

	for(auto iter = accelerators.begin(); iter != accelerators.end(); iter++)
	{
		Acceleration& accel = this->engine_.getComponentOf<Acceleration>(*iter);
		Velocity& vel = this->engine_.getComponentOf<Velocity>(*iter);
		vel += accel * elapsed.asSeconds();
	}

	std::vector<entity_id> movables = this->engine_.getEntitys(Position::getTypeBitID() | Velocity::getTypeBitID());
	
	for(auto iter = movables.begin(); iter != movables.end(); iter++)
	{
		Position& pos = this->engine_.getComponentOf<Position>(*iter);
		Velocity& vel = this->engine_.getComponentOf<Velocity>(*iter);
		pos += vel * elapsed.asSeconds();
		if(pos.x < -320)
			pos.x = 320;
		if(pos.x > 320)
			pos.x = -320;
	}

	entity_id player = this->engine_.getFirstEntity(Player::getTypeBitID());

	Player& playerc = this->engine_.getComponentOf<Player>(player);

	Velocity& vel = this->engine_.getComponentOf<Velocity>(player);
	if(jck::vector::mag(vel) > 1)
		playerc.rotation = jck::vector::atan(vel);
	if(jck::vector::mag(vel) > 240)
	{
		sf::Vector2f renorm = jck::vector::normalize(vel) * 240.0f;

		vel.x = renorm.x;
		vel.y = renorm.y;


	}

}