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
		for(auto iter = this->components_.begin(); iter != this->components_.end(); iter++)
		{
			iter->push_back(0);
		}
		int id = this->currentComponents_.size();
		this->currentComponents_.push_back(0);
		return id;
	} else
	{
		// theres a free id, clear the entity and return that instead
		int newId = *this->freeIds_.begin();
		for(unsigned int i = 0; i < this->components_.size(); i++)
		{
			this->components_[i][newId] = 0;
		}
		this->currentComponents_[newId] = 0;
		return newId;
	}
}

bool EntityEngine::deleteEntity(entity_id e_id)
{
	// if the id is free and isn't out of bounds, add it to the free list
	if(this->freeIds_.count(e_id) == 0 && e_id < this->entities_.size() && e_id >= 0)
	{
		this->freeIds_.insert(e_id);
		for(unsigned int i = 0; i < this->components_.size(); i++)
		{
			this->components_[i][e_id] = 0;
		}
		this->currentComponents_[e_id] = 0;
		return true;
	} else
	{
		return false;
	}
}


std::vector<entity_id> EntityEngine::getEntitys(component_type_bit c_id)
{
	std::vector<entity_id> ret;
	if(c_id == 0)
		return ret;
	for(unsigned int i = 0; i < this->currentComponents_.size(); i++)
	{
		// ask the entity if it has the specified components
		// make sure the entity isn't deleted
		if(this->freeIds_.count(i) == 0 && (this->currentComponents_[i] & c_id) == c_id)
		{
			ret.push_back(i);
		}
	}
	return ret;
}

entity_id EntityEngine::getFirstEntity(component_id c_id)
{
	for(unsigned int i = 0; i < this->currentComponents_.size(); i++)
	{
		// ask the entity if it has the specified components
		// make sure the entity isn't deleted
		if(this->freeIds_.count(i) == 0 && (this->currentComponents_[i] & c_id) == c_id)
		{
			return i;
		}
	}
	return 0;
}