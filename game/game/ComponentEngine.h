#pragma once

#include <vector>
#include <unordered_set>

#include "Component.h"
#include "Entity.h"
class ComponentEngine
{
public:
	ComponentEngine(void);
	~ComponentEngine(void);
	template <class T>
	component_id getNewComponent(void)
	{
		if(this->freeIds_.size() == 0)
		{
			int newId = this->components_.size();
			this->components_.push_back(new T());
			this->components_[newId]->id_ = newId;
			return newId;
		} else
		{
			int newId = *this->freeIds_.begin();
			this->freeIds_.erase(this->freeIds_.begin());
			
			if(this->components_[newId] != NULL)
				this->deleteComponent(newId);
			this->components_[newId] = new T();
			this->components_[newId]->id_ = newId;

			return newId;
		}
	}
	
	template <class T>
	bool giveNewComponent(Entity& ent)
	{
		entity_id id = this->getNewComponent<T>();
		return ent.addComponent(*this->getComponent(id));
	}

	bool deleteComponent(component_id id)
	{
		Component* toDelete = this->components_[id];
		if(toDelete != NULL)
		{
			this->components_[id] = NULL;
			delete toDelete;
			toDelete = NULL;
			return true;
		}
		return false;
	}
	template <class T>
	T* getComponentAs(component_id id)
	{
		return dynamic_cast<T*>(this->components_[id]);
	}
	
	template <class T>
	T* getComponentOf(Entity& ent)
	{
		return this->getComponentAs<T>(ent.getComponent(T::getTypeID()));
	}
	Component* getComponent(component_id id)
	{
		return this->components_[id];
	}
private:
	std::vector<Component*> components_;
	std::unordered_set<component_id> freeIds_;
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