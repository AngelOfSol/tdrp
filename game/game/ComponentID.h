#pragma once
#include "Component.h"

typedef unsigned long int component_id;

template <class T>
class ComponentID : public Component
{
public:
	ComponentID(void)
	{
	}
	~ComponentID(void)
	{
	}
	virtual component_type_id getType(void) const
	{
		return this->getTypeID();
	}
	static component_type_id getTypeID(void)
	{
		if(ComponentID::typeId_ == 0)
		{
			ComponentID::typeId_ = Component::getNewTypeID();
		}
		return ComponentID::typeId_;
	}
private:
	static component_type_id typeId_;
};
template <class T>
component_type_id ComponentID<T>::typeId_ = 0;