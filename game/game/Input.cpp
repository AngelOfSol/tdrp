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
	entity_id playerID = this->engine_.getFirstEntity(Player::getTypeBitID());

	InputData input = this->engine_.getComponentOf<InputData>(this->engine_.getFirstEntity(InputData::getTypeBitID()));

	Player& player = this->engine_.getComponentOf<Player>(playerID);

	Acceleration& accel = this->engine_.getComponentOf<Acceleration>(playerID);
	
	Velocity& vel = this->engine_.getComponentOf<Velocity>(playerID);

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
		accel += 2.0f * jck::vector::rotate(vel, Angle<float>(DEGREE, 90.0f));
	} else if(input.leftKey)
	{
		accel += 2.0f * jck::vector::rotate(vel, Angle<float>(DEGREE, -90.0f));
	}


}