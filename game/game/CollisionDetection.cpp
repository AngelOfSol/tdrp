#include "CollisionDetection.h"


CollisionDetection::CollisionDetection(Engine& engine):System(engine)
{
}


CollisionDetection::~CollisionDetection(void)
{
}

void CollisionDetection::start()
{
}

void CollisionDetection::stop()
{
}

void CollisionDetection::update(sf::Time elapsed)
{
	// get the player

	auto player = this->engine_.getFirstHandle(Player::getTypeBitID());

	const Position playerPos = player.get<Position>();

	const Velocity playerVel = player.get<Velocity>();

	// get the level data

	auto level = this->engine_.getFirstHandle(LevelData::getTypeBitID());

	LevelData& levelData = level.get<LevelData>();

	auto& indices = *levelData.indices;
	// mesh the player into the grid

	sf::Vector2f playerGridPos = playerPos / (float) levelData.length;
	sf::Vector2f playerGridVel = playerVel / (float) levelData.length;
	
	if(abs(playerGridVel.x) < 1)
	{
		playerGridVel.x = 1 * playerGridVel.x / abs(playerGridVel.x);
	}
	if(abs(playerGridVel.y) < 1)
	{
		playerGridVel.y = 1 * playerGridVel.y / abs(playerGridVel.y);
	}

	// cull out grid squares there aren't in the window

	sf::Vector2f lowerBound;
	sf::Vector2f upperBound;
	
	jck::vector::createBounds(playerGridPos, playerGridVel, &lowerBound, &upperBound);
	
	lowerBound = jck::vector::max(lowerBound, sf::Vector2f(0.0f, 0.0f));
	upperBound = jck::vector::min(upperBound, sf::Vector2f(indices.getSize(0), indices.getSize(1)));

	std::cout << playerGridPos.x << ", " << playerGridPos.y << std::endl;

	for(int i = lowerBound.x; i < upperBound.x; i++)
	{
		for(int j = lowerBound.y; j < upperBound.y; j++)
		{
			if((int)playerGridPos.x == i && (int)playerGridPos.y == j)
			{
				indices(i, j) = 1;
			} else
			{
				indices(i, j) = 0;
			}
		}
	}
	sf::
}