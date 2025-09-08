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
}

#endif //POOLOVERFLOWERROR_H
