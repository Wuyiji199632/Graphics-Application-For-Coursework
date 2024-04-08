#pragma once
#include <map>
#include <set>
#include <DX3D/Prerequisites.h>
#include <DX3D/Entity/Entity.h>
#include <DX3D/Game/Game.h>
class World
{
public:
	World(Game*game);
	~World();

	template <typename T>

	T* createEntity()
	{
		static_assert(std::is_base_of<Entity, T>::value, "T must inherit from Entity class");

		auto id = typeid(T).hash_code();

		auto e = new T();

		createEntityInternal(e, id);

		return e;
	}

	void update(float deltaTime);

	Game* getGame();
private:
	void createEntityInternal(Entity* entity, size_t id);
	void removeEntity(Entity* entity);

private:
	std::map<size_t, std::map<Entity*, std::unique_ptr<Entity>>> m_entities;

	std::set<Entity*> m_entitiesToDestroy;
	Game* m_game = nullptr;

	friend class Entity;
};

