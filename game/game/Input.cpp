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
	auto playerE = this->engine_.getFirstHandle(Player::getTypeBitID());

	InputData input = this->engine_.getFirstHandle(InputData::getTypeBitID()).get<InputData>();

	Player& player = playerE.get<Player>();

	Acceleration& accel = playerE.get<Acceleration>();
	
	Velocity& vel = playerE.get<Velocity>();

	if(input.upKey)
	{
		accel.x = 120.0f * cosf(player.rotation);
		accel.y = 120.0f * sinf(player.rotation);
	} else if(input.downKey)
	{
		accel.x = -0.99f * vel.x;
		accel.y = -0.99f * vel.y;
	} else
	{
		accel.x = 0;
		accel.y = 0;
	}

	if(input.rightKey)
	{
		accel += 5.0f * jck::vector::rotate(vel, Angle<float>(DEGREE, 100.0f));
	} else if(input.leftKey)
	{
		accel += 5.0f * jck::vector::rotate(vel, Angle<float>(DEGREE, -100.0f));
	}


}