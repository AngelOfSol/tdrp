#pragma once

#include <vector>
#include <unordered_set>
#include "ComponentEngine.h"
#include "typedefs.h"


/**
	@author Julien Kilian
	@version 1.0 2/18/2014

	An Engine class to manage the entities, creating and destroying them.

*/

class EntityEngine
{
public:
	EntityEngine(void);
	~EntityEngine(void);
	/**
		Gets a new entity.
		@return The entity ID of the new entity.
	*/
	entity_id getNewEntity(void);
	/**
		Attempts to delete the entity with the specified entity id.
		@param id The id to be deleted.
		@return Whether or not the entity was deleted.
	*/
	bool deleteEntity(entity_id id);
	/**
		Gets the pointer of an enitity with the specified ID.
		@param id The id to be gotten.
		@return A pointer to the entity.  Returns NULL if non existent.
	*/
	template <class T>
	component_id getComponent(entity_id id)
	{
		return this->components_[T::getTypeID()][id];
	}
	
	template <class T>
	bool addComponent(entity_id id, T component)
	{
		component_type_id typeId = T::getTypeID();
		component_type_bit typeBit = T::getTypeBitID();
		
		while(this->components_.size() <= typeId)
		{
			this->components_.push_back(std::vector<component_id>(this->currentComponents_.size()));
		}

		if((this->currentComponents_[id] & typeBit) == typeBit)
			return false;

		this->currentComponents_[id] |= typeBit;
		this->components_[typeId][id] = component.getId();

		return true;
	}

	/**
		Gets a set of entities that have all of the components flagged by type.
		@param types The types of components to check for.
		@return A list of pointers to entities that qualified.
	*/
	std::vector<entity_id> getEntitys(component_type_bit type);
	
	/**
		Gets the first entity that has all of the components flagged by type.
		@param types The types of components to check for.
		@return A pointer to the enitities that qualified.
	*/
	entity_id getFirstEntity(component_type_bit type);

	template <class T>
	bool hasComponent(entity_id id) const
	{
		if(this->freeIds_.count(id) > 0)
			return false;

		return (this->currentComponents_[id] & T::getTypeBitID()) == T::getTypeBitID();
	}
	
	bool exists(component_type_bit type) const;

private:
	std::unordered_set<entity_id> freeIds_;

	std::vector<std::vector<component_id>> components_;
	std::vector<component_type_bit> currentComponents_;

	friend class Engine;

	bool addRawComponent(entity_id id, component_id component, component_type_id typeId)
	{
		
		this->currentComponents_[id] |= 1 << typeId;
		this->components_[typeId][id] = component;

		return true;
	}

	component_id getRawComponent(entity_id id, component_type_id type)
	{
		return this->components_[type][id];
	}
};

/*
essentially remove the Entity class

move all data into a bunch of vectors

std::vector<std::vector<component_ids>> where the index of the first vector corresponds to the component type
and the index of the second vector corresponds to the entity

data[0][1] accesses the componentID of the second entity of the first component type

axis of similiarity is the component type

std::vecotr<component_type_id> has a bit flag set of the active components

*/