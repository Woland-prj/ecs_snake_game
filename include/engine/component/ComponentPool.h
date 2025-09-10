#ifndef COMPONENTPOOL_H
#define COMPONENTPOOL_H
#include "IComponentPool.h"
#include "PoolOverflowError.h"
#include "entity/EntityIdPool.h"

#include <vector>

namespace ecs_engine::component
{
template <typename T>
class ComponentPool final : public IComponentPool
{
public:
	explicit ComponentPool(size_t maxCount)
		: m_maxCount(maxCount)
		, m_data(static_cast<T*>(::operator new[](maxCount * sizeof(T))))
	{
	}

	~ComponentPool() override
	{
		::operator delete[](m_data);
	}

	void Allocate(entity::EntityId entityId, T&& initial)
	{
		if (entityId > m_maxCount)
			throw PoolOverflowError();
		new (&m_data[entityId]) T(std::forward<T>(initial));
	}

	void Deallocate(entity::EntityId entityId) override
	{
		auto ptr = m_data + entityId;
		ptr->~T();
	}

	T* Get(entity::EntityId entityId)
	{
		return m_data + entityId;
	}

private:
	size_t m_maxCount;
	T* m_data;
};
} // namespace ecs_engine::component

#endif // COMPONENTPOOL_H
