#ifndef POOLOVERFLOWERROR_H
#define POOLOVERFLOWERROR_H

#include <stdexcept>

namespace ecs_engine::component
{
class PoolOverflowError final : public std::runtime_error
{
public:
	PoolOverflowError()
		: std::runtime_error("pool overflow")
	{
	}
};
} // namespace ecs_engine::component

#endif // POOLOVERFLOWERROR_H
