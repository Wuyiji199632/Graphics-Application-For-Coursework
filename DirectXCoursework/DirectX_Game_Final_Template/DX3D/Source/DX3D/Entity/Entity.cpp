#include <DX3D/Entity/Entity.h>
#include <DX3D/Game/World.h>
Entity::Entity()
{
	m_transform = createComponent<TransformComponent>();
}

Entity::~Entity()
{
}

void Entity::release()
{
	m_world->removeEntity(this);
}

World* Entity::getWorld()
{
	return m_world;
}

InputSystem* Entity::getInputSystem()
{
   return m_world->getGame()->getInputSystem();;
}

TransformComponent* Entity::getTransform()
{
	return m_transform;
}

void Entity::createComponentInternal(Component* component, size_t id)
{
	auto componentPtr = std::unique_ptr<Component>(component);

	m_components.emplace(id, std::move(componentPtr));

	component->m_typeId = id;

	component->m_entity = this;

	component->onCreateInternal();
	
}

Component* Entity::getComponentInternal(size_t id)
{

	auto it = m_components.find(id);

	if (it == m_components.end()) return nullptr;


	return it->second.get();
}

void Entity::removeComponent(size_t id)
{
	m_components.erase(id);
}
