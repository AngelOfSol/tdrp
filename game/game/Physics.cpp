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
	
	auto accelerators = this->engine_.getHandles(Acceleration::getTypeBitID() | Velocity::getTypeBitID());

	for(auto iter = accelerators.begin(); iter != accelerators.end(); iter++)
	{
		Acceleration& accel = iter->get<Acceleration>();
		Velocity& vel = iter->get<Velocity>();
		vel += accel * elapsed.asSeconds();
	}

	auto movables = this->engine_.getHandles(Position::getTypeBitID() | Velocity::getTypeBitID());
	
	for(auto iter = movables.begin(); iter != movables.end(); iter++)
	{
		Position& pos = iter->get<Position>();
		Velocity& vel = iter->get<Velocity>();
		pos += vel * elapsed.asSeconds();
		
	}

	auto player = this->engine_.getFirstHandle(Player::getTypeBitID());

	Player& playerc = player.get<Player>();

	Velocity& vel = player.get<Velocity>();


	if(jck::vector::mag(vel) > 1)
	{
		playerc.rotation = jck::vector::atan(vel);
		player.get<Camera>().cameraAngle = -playerc.rotation - Angle<float>(DEGREE, 90);
	}
	if(jck::vector::mag(vel) > 240)
	{
		sf::Vector2f renorm = jck::vector::normalize(vel) * 240.0f;

		vel.x = renorm.x;
		vel.y = renorm.y;


	}
	std::cout << jck::vector::mag(vel) << std::endl;

}