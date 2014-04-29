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
	virtual component_type_id getTypeBit(void) const
	{
		return this->getTypeBit();
	}
	static component_type_id getTypeID(void)
	{
		if(ComponentID::typeBit_ == 0)
		{
			ComponentID::typeId_ = Component::getNewTypeID();
			ComponentID::typeBit_ = 1 << ComponentID::typeId_;
		}
		return ComponentID::typeId_;
	}
	static component_type_bit getTypeBitID(void)
	{
		if(ComponentID::typeBit_ == 0)
		{
			ComponentID::typeId_ = Component::getNewTypeID();
			ComponentID::typeBit_ = 1 << ComponentID::typeId_;
		}
		return ComponentID::typeBit_;
	}
private:
	static component_type_id typeId_;
	static component_type_bit typeBit_;
};
template <class T>
component_type_id ComponentID<T>::typeId_ = -1;
template <class T>
component_type_bit ComponentID<T>::typeBit_ = 0;