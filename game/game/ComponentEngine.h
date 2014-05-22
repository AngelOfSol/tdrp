#pragma once

#include <vector>
#include <unordered_set>

#include "ComponentList.h"
class ComponentEngine
{
public:
	ComponentEngine(void);
	~ComponentEngine(void);
	template <class T>
	T& getNewComponent(void)
	{
		component_type_id typeId = T::getTypeID();
		this->validateLists<T>();
		Component * temp = &this->componentLists_[typeId]->getNewComponent();
		return dynamic_cast<T&>(*temp);
	}
	
	template <class T>
	void deleteComponent(component_id id)
	{
		component_type_id typeId = T::getTypeID();
		this->validateLists<T>();
		this->componentLists_[typeId]->deleteComponent(id);
	}
	template <class T>
	T& getComponent(component_id id)
	{
		component_type_id typeId = T::getTypeID();
		this->validateLists<T>();
		return dynamic_cast<T&>(this->componentLists_[typeId]->getComponent(id));
	}

	friend class Engine; 
	
private:
	std::vector<ComponentListInterface*> componentLists_;
	template <class T>
	void validateLists()
	{
		component_type_id typeId = T::getTypeID();
		while(this->componentLists_.size() <= typeId)
		{
			this->componentLists_.push_back(NULL);
		}
		if(this->componentLists_[typeId] == NULL)
		{
			this->componentLists_[typeId] = new ComponentList<T>();
		}
	}

	component_id getNewRawComponent(component_type_id type)
	{
		return this->componentLists_[type]->getNewComponent().getId();
	}

	Component& getRawComponent(component_id id, component_type_id type)
	{
		return this->componentLists_[type]->getComponent(id);
	}

	void deleteRawComponent(component_id id, component_type_id type)
	{
		this->componentLists_[type]->deleteComponent(id);
	}
};

/*
ComponentListInterface
{
     Component* getComponent(id);
     id getNewComponent();
}

ComponentList<T>
: public ComponentListInterface
{
      Component* getComponent(id);
      id getNewComponent();
}

std::vector<ComponentEngine*>
std::vector<ComponentEngine&>


reimplement methods so that it works with


*/