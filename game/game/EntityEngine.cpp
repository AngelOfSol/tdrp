#include "EntityEngine.h"


EntityEngine::EntityEngine(void)
{
}


EntityEngine::~EntityEngine(void)
{
}

entity_id EntityEngine::getNewEntity(void)
{
	// checks to see if any ids are unused
	if(this->freeIds_.size() == 0)
	{
		// no free ids, so add a new one to the list
		int newId = this->entities_.size();
		this->entities_.push_back(Entity(newId));
		return newId;
	} else
	{
		// theres a free id, clear the entity and return that instead
		int newId = *this->freeIds_.begin();
		this->freeIds_.erase(this->freeIds_.begin());
		this->entities_[newId].removeAllComponents();
		return newId;
	}
}

bool EntityEngine::deleteEntity(entity_id e_id)
{
	// if the id is free and isn't out of bounds, add it to the free list
	if(this->freeIds_.count(e_id) == 0 && e_id < this->entities_.size() && e_id >= 0)
	{
		this->freeIds_.insert(e_id);
		return true;
	} else
	{
		return false;
	}
}

Entity* EntityEngine::getEntity(entity_id e_id)
{
	// check to make sure the entity isn't deleted, and the id is withing bounds
	if(this->freeIds_.count(e_id) == 0 && e_id < this->entities_.size() && e_id >= 0)
	{
		return &this->entities_[e_id];
	} else
	{
		return NULL;
	}
}
std::vector<Entity*> EntityEngine::getEntitys(component_id c_id)
{
	std::vector<Entity*> ret;
	for(auto iter = this->entities_.begin(); iter != this->entities_.end(); iter++)
	{
		// ask the entity if it has the specified components
		// make sure the entity isn't deleted
		if(this->freeIds_.count(iter->id_) == 0 && iter->hasComponents(c_id))
		{
			ret.push_back(&(*iter));
		}
	}
	return ret;
}