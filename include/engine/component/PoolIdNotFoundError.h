#ifndef POOLIDNOTFOUNDERROR_H
#define POOLIDNOTFOUNDERROR_H
#include <stdexcept>

namespace ecs_engine::component
{
class PoolIdNotFoundError final : public std::runtime_error
{
public:
	PoolIdNotFoundError()
		: std::runtime_error("pool id not found")
	{
	}
};
} // namespace ecs_engine::component

#endif // POOLIDNOTFOUNDERROR_H
