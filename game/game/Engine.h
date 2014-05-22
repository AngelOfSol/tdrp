#pragma once
#include "ComponentEngine.h"
#include "EntityEngine.h"

class Engine
{
public:
	Engine(void);
	~Engine(void);

	// entity engine helper methods

	entity_id getNewEntity(void) { return this->entities_.getNewEntity(); };

	template <class T>
	component_id getComponent(entity_id id)	{ return this->getComponent<T>(id)};

	template <class T>
	bool addComponent(entity_id id, T component) { return this->entities_.addComponent<T>(id, component); };

	std::vector<entity_id> getEntitys(component_type_bit type) { return this->entities_.getEntitys(type); };

	entity_id getFirstEntity(component_type_bit type) { return this->entities_.getFirstEntity(type); };

	template <class T>
	bool hasComponent(entity_id id) const { return this->entities_.hasComponent<T>(id); };

	bool exists(component_type_bit type) const { return this->entities_.exists(type); };

	// component engine helper methods

	template <class T>
	T& getNewComponent(void) { return this->components_.getNewComponent<T>(); };
	
	template <class T>
	T& getComponent(component_id id) { return this->components_.getComponent<T>(id); };

	// combined helper methods

	template <class T>
	T& getComponentOf(entity_id id)
	{
		return this->components_.getComponent<T>(this->entities_.getComponent<T>(id));
	}

	template <class T>
	bool addComponentTo(entity_id id)
	{
		if(this->hasComponent<T>(id))
			return false;
		return this->addComponent(id, this->getNewComponent<T>());
	}

	entity_id clone(entity_id id)
	{
		entity_id newEntity = this->getNewEntity();

		for(component_type_id typeId = 0; typeId < sizeof(component_type_bit) * 8; typeId++)
		{
			component_type_bit typeBit = 1 << typeId;
			if(this->hasComponentBit(id, typeBit))
			{
				component_id newComponent = this->components_.getNewRawComponent(typeId);
				this->entities_.addRawComponent(newEntity, newComponent, typeId);
			}
		}

		return newEntity;
	}

	bool deleteEntity(entity_id id) 
	{ 
		for(component_type_id typeId = 0; typeId < sizeof(component_type_bit) * 8; typeId++)
		{
			component_type_bit typeBit = 1 << typeId;
			if(this->hasComponentBit(id, typeBit))
			{
				this->components_.deleteRawComponent(this->entities_.getRawComponent(id, typeId), typeId);
			}
		}
		return this->entities_.deleteEntity(id); 
	};
	
	class Entity
	{
	public:
		template <class T>
		bool add()
		{
			return this->engine_.addComponentTo<T>(this->id_);
		}
		template <class T>
		T& get()
		{
			return this->engine_.getComponentOf<T>(this->id_);
		}
		template <class T>
		const T& get() const
		{
			return this->engine_.getComponentOf<T>(this->id_);
		}
		Entity clone() const
		{
			return Entity(this->engine_.clone(this->id_), engine_);
		}
		template <class T>
		bool has() const
		{
			return this->engine_.hasComponent<T>(this->id_);
		}
		bool hasTypes(component_type_bit ctb) const
		{
			return this->engine_.hasComponentBit(this->id_, ctb);
		}

		Engine& getEngine() const
		{
			return this->engine_;
		}

		entity_id getID() const
		{
			return this->id_;
		}
		~Entity()
		{
		}
	private:
		friend class Engine;
		Entity(entity_id id, Engine& engine):id_(id), engine_(engine)
		{
		}
		entity_id id_;
		Engine& engine_;
	};

	Entity getNewHandle(void) 
	{ 
		return Entity(this->entities_.getNewEntity(), *this); 
	};
	Entity getHandle(entity_id eid)
	{
		return Entity(eid, *this);
	}
	bool deleteHandle(Entity e)
	{
		this->deleteEntity(e.id_);
	}
	Entity getFirstHandle(component_type_bit ctb)
	{
		return Entity(this->getFirstEntity(ctb), *this);
	}
	std::vector<Entity> getHandles(component_type_bit ctb)
	{
		std::vector<entity_id> ids = this->getEntitys(ctb);

		std::vector<Entity> ret;

		for(auto iter = ids.begin(); iter != ids.end(); iter++)
		{
			ret.push_back(Entity(*iter, *this));
		}

		return ret;
	}
private:
	ComponentEngine components_;
	EntityEngine entities_;
	
	bool hasComponentBit(entity_id id, component_type_bit bit)
	{
		return (this->entities_.currentComponents_[id] & bit) == bit;
	}
};

