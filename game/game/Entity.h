#pragma once

#include <unordered_map>

#include "Component.h"

typedef unsigned long int entity_id;

/**
	@author Julien Kilian
	@version 1.0 2/18/2014

	An entity class that holds references to all components it may or may not have.
	Use an EntityEngine to create and manage them.  Holds only IDs, so pointers are managed elsewhere.

*/

class Entity
{
public:
	~Entity(void);
	/**
		Adds a component to the entity, as long as there isn't already one
		with the same type held by the component.
		@param component The component to be added to the entity.
		@return Whether or not the component was successfully added.
	*/
	bool addComponent(const Component& component);
	/**
		Removes a component of a specific type.
		@param type The type of component to be removed.
		@return Whether or not the component type was deleted.
	*/
	bool removeComponent(component_type_id type);
	/**
		Gets a component of a specific type.
		@param type The type of component to be retrieved.
		@return The component id of the component in question.  NULL is returned if it doesn't exist.
	*/
	component_id getComponent(component_type_id type);
	/**
		Checks to see if the entity contains the component types passed.  
		@param types A flag with bits set based on the type.
		@return Returns whether the entity has the provided types.
	*/
	bool hasComponents(component_type_id types) const;
	/**
		Dissassociates all components with this entity.
	*/
	void removeAllComponents();
private:
	friend class EntityEngine;
	Entity(entity_id);
	std::unordered_map<component_type_id, component_id> components_;
	const entity_id id_;
	component_type_id currentComponents_;
};