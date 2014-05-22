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
	
	// Accelerate things with velocities

	auto accelerators = this->engine_.getHandles(Acceleration::getTypeBitID() | Velocity::getTypeBitID());

	for(auto iter = accelerators.begin(); iter != accelerators.end(); iter++)
	{
		Acceleration& accel = iter->get<Acceleration>();
		Velocity& vel = iter->get<Velocity>();
		vel += accel * elapsed.asSeconds();
	}

	// Move things with positions

	auto movables = this->engine_.getHandles(Position::getTypeBitID() | Velocity::getTypeBitID());
	
	for(auto iter = movables.begin(); iter != movables.end(); iter++)
	{
		Position& pos = iter->get<Position>();
		Velocity& vel = iter->get<Velocity>();
		pos += vel * elapsed.asSeconds();
		
	}

	// Mantain player camera angle and placement
	// Mantain player max speed

	auto player = this->engine_.getFirstHandle(Player::getTypeBitID());

	Rotation& playerAngle = player.get<Rotation>();

	Velocity& vel = player.get<Velocity>();

	const Player& data = player.get<Player>();

	if(jck::vector::mag(vel) > 1)
	{
		playerAngle.value = jck::vector::atan(vel);
	}
	if(jck::vector::mag(vel) > data.maxSpeed)
	{
		sf::Vector2f renorm = jck::vector::normalize(vel) * data.maxSpeed;

		vel.x = renorm.x;
		vel.y = renorm.y;


	}
	//std::cout << jck::vector::mag(vel) << std::endl;

}