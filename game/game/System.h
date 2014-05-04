#pragma once

#include "Engine.h"

template <class T>
class System
{
public:
	System(Engine& engine):engine_(engine)
	{
	};
	virtual ~System(void)
	{
	};
	virtual void start() = 0;
	virtual void stop() = 0;
	virtual void update(T timeStep) = 0;
protected:
	Engine& engine_;
};

