#pragma once
#include "componentid.h"
#include "mdarray.h"
#include "typedefs.h"
#include <vector>

/*
	Flags an entity as holding level data, and provides a container to store them.

	md_array is a multi dimenionsal array holding indices.  The indices point to the <ids> vector which holds the entity_id they refer to.
*/
class LevelData :
	public ComponentID<LevelData>
{
public:
	LevelData(void);
	~LevelData(void);
	md_array<int, 2> * indices;
	std::vector<entity_id> ids;
	int length;
};

