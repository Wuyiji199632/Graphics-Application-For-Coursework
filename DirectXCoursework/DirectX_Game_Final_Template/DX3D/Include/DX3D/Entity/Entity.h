#pragma once
#include <DX3D/Prerequisites.h>
#include <map>
#include "Component/Component.h"
#include "Component/TransformComponent.h"
class Entity
{
public:
	Entity();
	virtual ~Entity();
	void release();
	World* getWorld();
	InputSystem* getInputSystem();
	TransformComponent* getTransform();

	template <typename T>

	T* createComponent()
	{
		static_assert(std::is_base_of<Component, T>::value, "T must inherit from Component class");

		auto c = getComponent<T>();

		if (!c) {

			auto id = typeid(T).hash_code();

			c = new T();

			createComponentInternal(c, id);

			return c;
		}

		return nullptr;
		
	}

	template <typename T>
	T* getComponent()
	{
		static_assert(std::is_base_of<Component, T>::value, "T must inherit from Component class");

		auto id = typeid(T).hash_code();
	
		return (T*)getComponentInternal(id);
	}

protected:
	virtual void onCreate(){}
	virtual void onUpdate(float deltaTime){}
	size_t m_typeId = 0;
	World* m_world=nullptr;
	TransformComponent* m_transform=nullptr;
	std::map<size_t, std::unique_ptr<Component>> m_components;
	friend class World;
private:
	void createComponentInternal(Component* component, size_t id);
	Component* getComponentInternal(size_t id);
	void removeComponent(size_t id);
	friend class Component;

};

