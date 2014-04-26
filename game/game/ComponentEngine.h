#pragma once

#include <vector>
#include <unordered_set>

#include "Component.h"

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
	Component* getComponent(component_id id)
	{
		return this->components_[id];
	}
private:
	std::vector<Component*> components_;
	std::unordered_set<component_id> freeIds_;
};

