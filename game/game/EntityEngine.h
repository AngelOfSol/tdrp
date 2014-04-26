#pragma once

#include <vector>
#include <unordered_set>

#include "Entity.h"

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
	Entity* getEntity(entity_id id);
	/**
		Gets a set of entities that have all of the components flagged by type.
		@param types The types of components to check for.
		@return A list of pointers to entities that qualified.
	*/
	std::vector<Entity*> getEntitys(component_type_id type);
	
private:
	std::vector<Entity> entities_;
	std::unordered_set<entity_id> freeIds_;
};

