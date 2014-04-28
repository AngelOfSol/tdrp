#pragma once

#include "EntityEngine.h"
#include "ComponentEngine.h"

template <class T>
class System
{
public:
	System(EntityEngine& engine, ComponentEngine& componentEngine):entitiesList_(engine), componentsList_(componentEngine)
	{
	};
	virtual ~System(void)
	{
	};
	virtual void start() = 0;
	virtual void stop() = 0;
	virtual void update(T timeStep) = 0;
protected:
	EntityEngine& entitiesList_;
	ComponentEngine& componentsList_;
};

