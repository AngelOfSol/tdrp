#include "Component.h"


Component::Component()
{
}


Component::~Component(void)
{
}

int Component::nextTypeId_ = 0;

component_type_id Component::getNewTypeID(void)
{
	// returns 2 to the power of nextId_
	// then increments nextId_
	return nextTypeId_++;
}