#ifndef SPARSESET_H
#define SPARSESET_H
#define DEFAULT_MAX_ENTITIES 100
#include "Signature.h"

#include <vector>
#include <cassert>

namespace ecs_engine::core
{
#include <vector>
#include <cassert>

template <typename T> class SparseSet
{
private:
	std::vector<T> dense;
	std::vector<size_t> sparse;
	size_t count = 0;
	const size_t maxEntities;

public:
	explicit SparseSet()
		: dense(DEFAULT_MAX_ENTITIES), sparse(DEFAULT_MAX_ENTITIES), count(0), maxEntities(DEFAULT_MAX_ENTITIES)
	{
	}

	explicit SparseSet(size_t maxEntities)
		: dense(maxEntities), sparse(maxEntities), count(0), maxEntities(maxEntities)
	{
	}

	bool Contains(T e) const
	{
		return e < maxEntities && sparse[e] < count && dense[sparse[e]] == e;
	}

	void Add(T e)
	{
		if (Contains(e))
			return;
		assert(e < maxEntities);
		dense[count] = e;
		sparse[e] = count;
		++count;
	}

	void Remove(T e)
	{
		if (!Contains(e))
			return;
		size_t idx = sparse[e];
		T last = dense[count - 1];
		dense[idx] = last;
		sparse[last] = idx;
		--count;
	}

	void Clear()
	{
		count = 0;
	}

	size_t Size() const
	{
		return count;
	}

	const T* Data() const
	{
		return dense.data();
	}
};
}


#endif //SPARSESET_H
