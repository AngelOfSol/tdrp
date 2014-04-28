#include "Entity.h"


Entity::Entity(entity_id e_id):id_(e_id), currentComponents_(0)
{
}


Entity::~Entity(void)
{
}

component_id Entity::getComponent(component_type_id t_id)
{
	if(this->hasComponents(t_id))
	{
		return this->components_[t_id];
	}
	return NULL;
}

bool Entity::addComponent(const Component& component)
{
	// checks to see if the component type is already occupied
	if(!this->hasComponents(component.getType()))
	{
		this->components_[component.getType()] = component.getId();
		this->currentComponents_= this->currentComponents_ | component.getType();
		return true;
	} else
	{
		return false;
	}
}

bool Entity::removeComponent(component_type_id t_id)
{
	// checks to see if the component exists before deleting it
	if(this->hasComponents(t_id))
	{
		return this->components_.erase(t_id) == 1;
		
	}
	return false;
}

bool Entity::hasComponents(component_id c_id) const
{
	// mask the current components to find set flags
	return (this->currentComponents_ & c_id) == c_id;
}

void Entity::removeAllComponents()
{
	// basic removal of all components
	this->components_.clear();
	this->currentComponents_ = 0;
}