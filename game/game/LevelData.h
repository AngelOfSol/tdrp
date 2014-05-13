#pragma once
#include "componentid.h"
#include "mdarray.h"
#include "typedefs.h"
#include <vector>
class LevelData :
	public ComponentID<LevelData>
{
public:
	LevelData(int x, int y);
	~LevelData(void);

	md_array<int, 2> indices;

	std::vector<entity_id> ids;
};

