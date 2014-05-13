#pragma once
#include <unordered_map>
#include <string>

#include "typedefs.h"

/**
	@author Julien Kilian
	@version 1.0 2/18/2014

	A component class that holds data.
	Use an ComponentEngine to create and manage them.  Holds only data.

*/

class Component
{
public:
	virtual ~Component(void);
	/**
		Gets the component id of the component.
		@return The component id of the component.
	*/
	component_id getId() const { return this->id_; };
	/**
		Gets the component type id.
		@return The type id of  thecomponent.
	*/
	virtual component_type_id getType() const = 0;
	virtual component_type_bit getTypeBit() const = 0;
protected:
	template <class T>
	friend class ComponentList;
	Component(void);
	component_id id_;
	static component_type_id getNewTypeID();
private:
	// the shift value of the next class id to be created
	static int nextTypeId_;
};

