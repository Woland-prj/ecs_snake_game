#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H
#include "ComponentPool.h"
#include "PoolAlreadyExistsError.h"
#include "PoolIdNotFoundError.h"

#include <iostream>
#include <typeindex>
#include <unordered_map>
#include <memory>

namespace ecs_engine::component
{
class PoolIdNotFoundError;

using PoolRegistry = std::vector<std::unique_ptr<IComponentPool>>;
using PoolId = size_t;

class ComponentManager
{
private:
	PoolRegistry m_poolRegistry;
	size_t m_maxPoolSize;
	size_t m_poolCounter = 0;

	std::unordered_map<std::type_index, PoolId> m_typeToIdMap;

public:
	explicit ComponentManager(size_t maxPoolSize);
	~ComponentManager() = default;

	template <typename T>
	PoolId RegisterComponent()
	{
		try
		{
			(void)GetPoolId<T>();
			throw PoolAlreadyExistsError(typeid(T).name());
		}
		catch (const std::exception& ex)
		{
			auto pool = std::make_unique<ComponentPool<T>>(m_maxPoolSize);
			const auto id = m_poolCounter++;
			m_typeToIdMap[typeid(T)] = id;
			m_poolRegistry.push_back(std::move(pool));
			return id;
		}
	}

	template <typename T>
	[[nodiscard]] PoolId GetPoolId() const
	{
		if (const auto it = m_typeToIdMap.find(typeid(T)); it != m_typeToIdMap.end())
		{
			return it->second;
		}
		throw PoolIdNotFoundError();
	}

	template <typename T>
	PoolId CreateComponent(const entity::EntityId entityId, T&& initialVal) const
	{
		const PoolId id = GetPoolId<T>();
		auto* pool = static_cast<ComponentPool<T>*>(m_poolRegistry[id].get());
		pool->Allocate(entityId, std::forward<T>(initialVal));
		return id;
	}

	template <typename T>
	T* GetComponent(entity::EntityId entityId)
	{
		const PoolId id = GetPoolId<T>();
		auto pool = static_cast<ComponentPool<T>*>(m_poolRegistry[id].get());
		return pool->Get(entityId);
	}

	template <typename T>
	PoolId DestroyComponent(const entity::EntityId entityId)
	{
		const auto id = m_typeToIdMap[typeid(T)];
		m_poolRegistry[id]->Deallocate(entityId);
		return id;
	}

	void DestroyComponent(entity::EntityId entityId, PoolId poolId) const;
};

} // namespace ecs_engine::component

#endif // COMPONENTMANAGER_H
