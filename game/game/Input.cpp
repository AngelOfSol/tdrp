#include "Input.h"


Input::Input(Engine& engine):System(engine)
{
}


Input::~Input(void)
{
}

void Input::start()
{
}

void Input::stop()
{
}

void Input::update(sf::Time elapsed)
{
	// Grab relevant player data

	auto playerE = this->engine_.getFirstHandle(Player::getTypeBitID());

	InputData input = this->engine_.getFirstHandle(InputData::getTypeBitID()).get<InputData>();

	Rotation& rotation = playerE.get<Rotation>();

	Acceleration& accel = playerE.get<Acceleration>();
	
	Velocity& vel = playerE.get<Velocity>();

	const Player& data = playerE.get<Player>();

	// Accelerate player in his direction if holding forwards, otherwise brake.

	if(input.upKey)
	{
		accel.x = data.accel * cosf(rotation.value);
		accel.y = data.accel * sinf(rotation.value);
	} else if(input.downKey)
	{
		accel.x = data.brakes * vel.x;
		accel.y = data.brakes * vel.y;
	} else
	{
		accel.x = 0;
		accel.y = 0;
	}

	// Turn the player while reducing velocity

	// Angle will determine how fast a turn is made, and how much velocity is kept through out the turn.

	if(input.rightKey)
	{
		accel += data.turnMultiplier * jck::vector::rotate(vel, data.turnAngle);
	} else if(input.leftKey)
	{
		accel += data.turnMultiplier * jck::vector::rotate(vel, -data.turnAngle);
	}


}