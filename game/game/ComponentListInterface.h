#pragma once
#include "Component.h"

class ComponentListInterface
{
public:
	ComponentListInterface(void);
	virtual ~ComponentListInterface(void);
	virtual Component& getNewComponent() = 0;
	virtual void deleteComponent(component_id) = 0;
	virtual Component& getComponent(component_id) = 0;
};

