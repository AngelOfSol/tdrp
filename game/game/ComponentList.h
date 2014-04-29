#pragma once
#include <vector>
#include "componentlistinterface.h"
template <class T>
class ComponentList :
	public ComponentListInterface
{
public:
	ComponentList(void)
	{
	}
	~ComponentList(void)
	{
	}
	Component& getNewComponent()	
	{
		if(this->freeIds_.size() == 0)
		{
			int newId = this->components_.size();

			this->components_.push_back(T());
			this->components_[newId].id_ = newId;

			return this->components_[newId];
		} else
		{
			int newId = *this->freeIds_.begin();
			this->freeIds_.erase(this->freeIds_.begin());
			
			this->components_[newId] = T();
			this->components_[newId].id_ = newId;

			return this->components_[newId];
		}
	}
	void deleteComponent(component_id id)
	{
		this->components_[id] = T();
		this->freeIds_.insert(id);
	}
	Component& getComponent(component_id id)
	{
		return this->components_[id];
	}
	
private:
	std::vector<T> components_;
	std::unordered_set<component_id> freeIds_;
};
